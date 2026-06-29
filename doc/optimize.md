# RCompiler 优化总结

本文档是当前优化工作的收束版，记录已经接入编译器的优化、基本实现方式、适用场景，以及当前真实的优化 pass 流程。后续维护时应以本文档和 `main.cpp`、`src/linearScan/regalloc.h` 的实际调用顺序为准。

## 0. 基本约束

- 目标后端是 RV64GC / lp64d 汇编。
- `usize/isize` 是 64-bit，涉及栈槽、load/store、常量折叠和函数调用时都必须保持 64-bit 语义。
- 后端优化尽量只使用已经确认可被 OJ 接受的 RV64 指令形态，避免再次触发 `CE_ASM`。
- 正确性验证使用 `riscv64-linux-gnu-gcc -static` 和 `qemu-riscv64`，不要用只支持 RV32 的 REIMU。
- OJ 优化分的主要瓶颈来自数组/结构体访问、循环、重复 helper call、分支、寄存器压力和 spill/reload。

## 1. 当前优化 Pipeline

入口在 `main.cpp`。当前实际 IR pipeline 是：

```text
IR generation
SROA
Mem2Reg
DominantTree
SCCP
FunctionInline
SCCP
ConstantFold
CFGClean
ConstantFold
CFGClean
DCE
MemoryForward
ConstantFold
CFGClean
StrengthReduction
LocalCSE
MemoryForward
ConstantFold
CFGClean
LICM
DCE
InstrSelect
Peephole(pre-regalloc)
ASM DCE
LinearScan
Peephole(post-regalloc)
ASMPrinter
```

后端调用顺序在 `src/linearScan/regalloc.h`：

```text
InstrSelect.select
Peephole.optimize(..., false)
LinearScan.deadCodeElimination
LinearScan.process
Peephole.optimize(..., true)
ASMPrinter.print
```

几个重复 pass 是有意安排：

- `FunctionInline` 后重跑 `SCCP`，让内联暴露出的常量和分支继续传播。
- `MemoryForward` 后重跑 `ConstantFold/CFGClean`，因为 load/store 转发经常制造常量分支和死块。
- `LocalCSE` 后再跑一次 `MemoryForward`，因为 getptr 和地址表达式被合并后，内存转发能识别更多等价地址。
- `LICM` 放在后段，避免提前 hoist 那些本来可以被转发、折叠或删除的临时。
- 最后一轮 `DCE` 删除 LICM/CSE/Forwarding 后留下的纯死计算。

## 2. IRBuilder 和 Lowering 阶段优化

### 2.1 常量提前求值

实现位置：

- `src/semantic/ConstEvaluator.h`
- `src/ir/IRBuilder.h`
- `src/ir/IRGlobalbuilder.h`

基本做法：

- 顶层 `const` 和关联常量优先在语义/IR 构建阶段求值。
- 对 `const path`、整数后缀、数组长度表达式做提前解析。
- 让后续 IR pass 直接看到 literal，而不是全局内存读取。

适用场景：

- `opti_compute_hash_mix`
- `opti_ntt_convolution`
- 使用大量模数、数组长度、结构体关联常量的样例

注意事项：

- `usize/isize` 常量必须保留 64-bit 精度。
- 不能把当前语言规范未支持的 Rust 类型当作优化方向。

### 2.2 Typed Array Initializer Copy Elision

实现位置：

- `src/ir/IRBuilder.h`

基本做法：

- 对 `let a: [T; N] = [ ... ];` 这种显式数组初始化，如果 initializer 已经生成了同形状数组对象，直接把该对象绑定为局部变量。
- 避免再分配一个目标数组并发出整块 `IRMemcpy`。

适用场景：

- 大数组初始化
- 图/NTT/DP 中的临时数组构造
- 隐藏点里局部数组初始化后马上进入热循环的情况

收益来源：

- 减少一次完整数组 copy。
- 降低初始 IR 体积和后端内存流量。

风险边界：

- 只在类型形状完全一致时直接绑定。
- 不能改变变量名绑定和作用域查找结果。

## 3. IR 优化 Pass

CR 时建议重点讲下面几项。`Mem2Reg`、`DominantTree`、`ConstantFold`、`CFGClean`、`DCE` 和 `StrengthReduction` 仍然在真实 pipeline 里，但文档里只作为辅助清理 pass 简述，不再单独展开。

### 3.1 SROA

实现位置：

- `src/optimize/sroa.h`

基本做法：

- 识别局部 `alloca` 的小 struct 或小 fixed array。
- 当前限制字段/元素数不超过 4。
- 只拆标量字段：整数和指针。
- 地址不逃逸、访问路径是常量字段/常量下标时，将聚合对象拆成多个 scalar alloca。
- 支持安全的 `memset 0` 和候选对象之间的 `memcpy` 初始化。

适用场景：

- 小结构体频繁读写。
- 结构体池中的小对象。
- helper 函数里的临时聚合对象。

核心收益：

- 把“结构体/小数组内存访问”拆成独立标量。
- 拆出来的字段可以继续被 SSA promotion、SCCP、CSE 和 DCE 优化。

### 3.2 SCCP

实现位置：

- `src/optimize/sccp.h`

基本做法：

- 使用 `Unknown / Constant / Overdefined` 三值 lattice。
- 只沿 executable edge 传播，避免把不可达分支的值混进 phi。
- 折叠 `IRPHI`、legacy bool phi、二元运算、cast 和常量分支。
- 支持 branch edge facts，例如 `x == c` 的 true edge 上记录 `x = c`。

适用场景：

- inline 后暴露出的常量参数。
- 状态机中的固定分支。
- bool 短路表达式。
- `if (x == const)` 分支内部继续使用 `x` 的代码。

核心收益：

- 删除不可达分支。
- 把 phi 折成常量或单值。
- 给 CFG clean 和 DCE 制造机会。

### 3.3 Function Inline

实现位置：

- `src/optimize/functionInline.h`

基本做法：

- 收集函数、调用次数和调用图。
- 排除 `main`、递归函数、多基本块函数和复杂返回类型。
- 用 cost model 控制 inline，单调用/tiny/scalar-memory helper 更容易 inline。
- inline 后把实参映射到形参，复制函数体，返回值接回调用点。

适用场景：

- 小算术 helper。
- getter/setter。
- 模运算 wrapper。
- 只调用一次的工具函数。

核心收益：

- 消除 call/return 和参数搬运开销。
- 暴露常量、地址表达式和 store-load 链给后续 pass。

风险边界：

- 过度 inline 会扩大 live range，增加后端 spill。
- long-param、大聚合参数、解释器 dispatch 类代码不能盲目 inline。

### 3.4 MemoryForward

实现位置：

- `src/optimize/memoryForward.h`

基本做法：

- 沿支配树维护已知 memory state。
- 对同一精确地址做 store-load forwarding。
- 对同一精确地址做 dominated load reuse。
- 删除被后续 store 覆盖、且中间没有读取的旧 store。
- 对结构体字段路径做保守 alias 判断：同根对象、不同常量字段可以认为不别名。

适用场景：

- 结构体字段反复读写。
- 解释器状态字段 load 后马上使用。
- 数组/结构池中同地址重复 load。
- `store v, p; load p` 这种 lowering 形态。

核心收益：

- 减少 IR load/store。
- 把 load 结果替换成 literal 或已有 SSA 值，继续触发常量折叠和死代码删除。

### 3.5 LocalCSE / Dominator GVN

实现位置：

- `src/optimize/localCSE.h`

基本做法：

- 构建 CFG、RPO 和支配树。
- 沿支配树传播表达式表。
- 对纯表达式做 CSE/GVN：
  - `IRBinaryop`
  - `IRGetptr`
  - `IRSext/IRZext/IRTrunc`
  - 保守 load CSE
- key 中包含 op、操作数、类型、`utag/i8tag/w64tag` 等语义标记。

适用场景：

- 数组地址重复计算。
- hash/NTT/DP 中相同二元表达式重复出现。
- 分支合流后同一 getptr/cast 被重复生成。

核心收益：

- 减少重复 IR 计算。
- 让后端看到更短的地址链。
- 让 MemoryForward 更容易识别等价地址。

### 3.6 LICM

实现位置：

- `src/optimize/licm.h`

基本做法：

- 用 back edge 识别 natural loop。
- 只处理有唯一 preheader 的循环。
- loop 内存在 call-like barrier 时跳过该 loop。
- hoist 循环不变量：
  - 较贵 scalar binary，如 mul/div/mod/shift。
  - 纯 getptr。
  - cast。
  - 服务 getptr 地址链的 cheap `add/sub`。
- 不 hoist load。

适用场景：

- NTT、image kernel、array transform 中的循环不变地址/尺度计算。
- 循环内重复 cast 和 getptr。

核心收益：

- 减少热循环内的重复算术和地址计算。

风险边界：

- 不提升 load，避免 alias 错误。
- cheap binary hoist 只保留地址链相关场景，避免 live range 过长。

### 3.7 辅助 IR 清理 Pass

这些 pass 在实现中存在，也在 pipeline 中启用，但 CR 时可以一句带过：

- `Mem2Reg / DominantTree`: 把局部标量栈槽提升到 SSA，给 SCCP/CSE/LICM 提供更干净的数据流。
- `ConstantFold`: 折叠局部常量表达式、cast、常量 getptr 和常量分支。
- `CFGClean`: 删除不可达块，清理 phi 输入，把单值 phi 替换成普通值。
- `DCE`: 从 return/branch/store/call 等有副作用指令反向标记 live 值，删除无用纯计算。
- `StrengthReduction`: 只保留明确安全的 power-of-two 转换，如 `x * 2^k -> x << k` 和 unsigned `/ % 2^k`。

## 4. 后端优化

### 4.1 指令选择优化

实现位置：

- `src/linearScan/InstrSelect.h`

基本做法：

- 常量尽量用 `li` 或 12-bit immediate 形式。
- 二元运算选择 immediate form，例如 `addi/andi/ori/xori/slti/sltiu`。
- getptr 常量偏移尽量直接体现在地址计算中。
- load/store 根据 `w64tag` 选择 `ld/sd`，普通 i32 使用 `lw/sw`。
- 函数调用记录真实 `callArgCount`，供后端 liveness 使用。
- 生成 frame placeholder，由寄存器分配阶段统一决定真实 prologue/epilogue。

适用场景：

- 小常量运算密集代码。
- 数组/结构体字段访问。
- 参数数量不同的 call。

风险边界：

- `u32/i32` 与 `usize/isize` 的扩展语义必须正确。
- 栈上传参和隐藏 return pointer 不能破坏 ABI。

### 4.2 Pre-regalloc Peephole

实现位置：

- `src/linearScan/Peephole.h`

当前主要优化：

- 删除 self move 和 `addi x, x, 0`。
- 将 `seqz/snez/slt/slti + bnez` 折成直接条件分支。
- 将 `addi/mv addr, base; load/store 0(addr)` 折成 `load/store off(base)`，要求 offset 能放入 12-bit。
- 将单 use 的 `mv tmp, src; op ..., tmp` 折进下一条指令。
- 识别小型 modular helper 并在 call site 内联：
  - `add_mod(a, b)`
  - `sub_mod(a, b)`
  - `norm(x)` 取模后负数补模

适用场景：

- `opti_ntt_convolution` 的模加/模减。
- `opti_graph_algorithms_suite` 中 `norm` helper。
- 状态机/解释器中的 bool 比较后马上分支。
- 数组访问中临时地址只用一次。

收益来源：

- 减少 call。
- 减少 bool 临时寄存器。
- 缩短地址链，降低寄存器压力。

风险边界：

- modular helper 通过函数体语义模式识别，不只靠函数名；但仍要求结构匹配。
- 内联序列只使用当前已验证的 RV64 指令。

### 4.3 ASM DCE

实现位置：

- `src/linearScan/LinearScan.h`

基本做法：

- 在寄存器分配前按函数构建 CFG。
- 做物理/虚拟寄存器 live 分析。
- 删除无副作用且结果不再使用的 asm 指令。
- 删除 `j/jr` 之后同块内不可达指令。

适用场景：

- IR DCE 后仍残留的汇编级临时。
- peephole 折叠后产生的无用 move/li。

风险边界：

- call、store、branch、jump、return 等必须保留。

### 4.4 Linear Scan Register Allocation

实现位置：

- `src/linearScan/LinearScan.h`

当前策略：

- 按函数划分 asm blocks。
- 构建 CFG 和 liveIn/liveOut。
- 为虚拟寄存器构造 live ranges，并允许同一物理寄存器被非重叠 range 复用。
- 对循环块加权，回边覆盖的 block use weight 更高，spill 选择优先保留热循环值。
- 对跨 call 的 interval 优先尝试 callee-saved 寄存器。
- call 只把实际使用的 `a0-a7` 参数寄存器计为 use，不再默认所有参数寄存器都 live。
- 收集 `mv v1, v2` copy hints，尝试把相关虚拟寄存器分到同一物理寄存器。
- 根据 weighted use density 选择 spill victim。
- 对单定义 `li` 形式的可重建值，spill rewrite 时可重新 materialize，避免分配真实 spill slot。
- 同一条指令中 use/def 都 spill 的虚拟寄存器复用 scratch，避免重复 load。

适用场景：

- 解释器大循环。
- 图算法和 range structure 中长 live range。
- NTT/hash pipeline 中临时多、call 少或 call 集中的函数。

收益来源：

- 降低热点循环中的 spill/reload。
- 减少 call 周围不必要的 caller-saved 压力。
- 降低 `mv` 链造成的虚拟寄存器数量。

风险边界：

- 当前仍不是完整图染色，也没有强 live range splitting。
- 复杂 next-use spill 选择尝试过但回退，因为线性编号不能准确表达 loop-carried value。
- 非重叠 spill slot 复用尝试过但回退，隐藏点出现明显负优化。

### 4.5 栈帧和 ABI 优化

实现位置：

- `src/linearScan/LinearScan.h`

当前优化：

- leaf function 不保存/恢复 `ra`。
- 没有 call、alloca、spill、callee-saved 使用的 leaf function 直接省略 frame setup。
- 只保存实际用到的 callee-saved 寄存器。
- frame size 16 字节对齐。
- 大 frame offset 超出 12-bit 时使用 `li + add + ld/sd`。

适用场景：

- 小 helper 函数。
- inline 后剩下的简单 leaf 函数。
- 递归工具函数中非叶子/叶子混合场景。

风险边界：

- 任何 caller-saved/callee-saved 误判都会导致 WA。
- 省略 frame 时必须保证没有本地栈槽、spill 或需要保存的寄存器。

### 4.6 Post-regalloc Peephole

实现位置：

- `src/linearScan/Peephole.h`

当前主要优化：

- 删除跳到下一块的 fallthrough `j`。
- 清理同基本块内冗余 stack access：
  - `ld slot` 后重复 `ld slot`，改为 `mv` 或直接复用。
  - `sd same-value slot` 删除。
  - 被后续 store 覆盖且中间没有读取的 store 删除。
  - 同时处理 12-bit offset 栈访问和 large-frame 的 `li + add + ld/sd` 形态。
- 复用已 materialize 的 frame address：
  - 重复 `li off; add addr, off, s0` 可改成 `mv addr, previousAddr`。
- 再次做 address fold 和 move fold。

适用场景：

- spill 很多的大函数。
- frame 很大的 long-param/隐藏性能点。
- 图/解释器/索引类样例中大量局部状态落栈的函数。

风险边界：

- 只做同基本块内的数据流，不跨 label/call/branch。
- 遇到未知 store、call、terminator 或 frame base 被改写时清空状态。

## 5. 各类隐藏点对应的主要优化

| 场景 | 主要优化 |
|---|---|
| 大数组循环 | Mem2Reg, LocalCSE, MemoryForward, LICM, address peephole |
| NTT / 模运算 | ConstantFold, StrengthReduction, modular helper inline, LICM |
| 图算法 | typed array copy elision, getptr CSE, MemoryForward, `norm` helper inline, spill cleanup |
| 结构体池 | SROA, alias-aware MemoryForward, DCE |
| 状态机/解释器 | SCCP, CFGClean, bool branch peephole, register allocation pressure control |
| hash pipeline | FunctionInline, SCCP, ConstantFold, LocalCSE, conservative LICM |
| long-param / 大 frame | actual call arg liveness, frame address reuse, large-frame stack cleanup |
| 小 helper 密集调用 | FunctionInline, leaf frame omission, modular helper inline |

## 6. 已尝试但当前不采用的方向

### 6.1 Graph Coloring Register Allocation

曾单独开分支实现图染色寄存器分配，但 OJ 表现不如当前 linear scan，且一度出现 codegen TLE 和 `opti_bytecode_vm_interpreter` 0 分。当前主线仍使用 `src/linearScan`。

结论：

- 图染色要达到收益，需要完整 coalescing、spill cost、callee-save cost、快速构图和可靠 rewrite。
- 当前实现成本高、风险大，不适合作为最终主线。

### 6.2 Aggressive Next-use Spill Choice

尝试用下一次 use 选择 spill victim，后来回退。

原因：

- 当前 next-use 基于线性指令编号，不理解 loop-carried value。
- 在解释器/状态机大循环中会把动态上很快使用的值误判为“很久不用”，导致热点循环 spill 爆炸。

### 6.3 Non-overlapping Spill Slot Reuse

尝试复用不重叠 spill slot，后来回退。

原因：

- 对性能没有稳定收益，并引入隐藏点负优化。
- 当前更稳定的收益来自减少 spill traffic，而不是压缩 spill slot 个数。

### 6.4 Near-power-of-two Multiply Expansion

尝试 `x * (2^k +/- 1)` 展开，后来收窄。

原因：

- RV64GC 有 `mul`，展开成 `slli + add/sub` 不一定更快。
- 展开会增加指令数和临时寄存器，可能造成更严重 spill。

### 6.5 过度收紧/放宽 Inline 和 LICM

多轮 OJ 反馈表明：

- 过度 inline scalar-memory helper 会让部分样例受益，但伤害 sort/hashmap/compression/index 等更大样例。
- LICM 过度 hoist cheap binary 会拉长 live range，解释器和长 pipeline 容易负优化。

最终策略：

- Inline 维持 cost model 和 growth budget。
- LICM cheap binary 只保留服务 getptr 地址链的 `add/sub`。

### 6.6 Global2Local

当前未实现为主线 pass。

原因：

- 当前顶层 `const` 大多已经在前端/IRBuilder 折成 literal。
- 没有稳定看到大量真实 `IRGlobal` load/store 热点。
- 隐藏性能点更主要是数组、结构体、循环和后端寄存器压力。

如果未来要做，第一版应只处理单函数使用、地址不逃逸、标量 load/store 的 global，并放在 `Mem2Reg` 前。

## 7. 验证基线

每次非文档改动后至少跑：

```bash
cmake --build build
```

然后用 RV64/qemu 流程跑：

```bash
bash /tmp/qemu_test.sh
bash /tmp/qt2.sh RCompiler-Testcases/long-param/src
```

如果 `/tmp` 脚本不存在，用等价流程：

```bash
./build/RCompiler < test.rx > test.s 2> test_builtin.s
cat test_builtin.s >> test.s
riscv64-linux-gnu-gcc -static -o test test.s
qemu-riscv64 test < test.in > test.out
```

当前维护的基线口径：

- `semantic-2`: 50/50
- `long-param`: 当前本地为 34/34
- `semantic-1 compileexitcode`: 221/221 active
- `semantic-1 RV64 link`: 114/114 pass cases

## 8. 后续维护建议

- 不要再盲目堆 IR pass；当前 IR 层基础优化已经比较完整。
- 新优化优先用隐藏点或本地等价 microbench 证明瓶颈存在。
- 任何可能增加 live range 的优化都要同时观察 spill/reload。
- 后端仍是和 O1 差距最大的方向，但要避免再次切换到未成熟图染色。
- 若继续优化，优先方向是更精确的 live range splitting、跨块 spill value dataflow、以及更强但可控的 copy coalescing。
