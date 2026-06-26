# RCompiler Optimization Plan

本文档记录下一阶段优化方向。`semantic-1`、`semantic-2`、`long-param` 只作为正确性回归集；优化收益以 OJ 的 17 个隐藏性能点为主，不再用 `semantic-2` 的静态汇编变化判断总体收益。

## 0. 当前约束

- IR 层优化已基本进入调参阶段；下一阶段允许做后端优化，但仍暂时不要新增 OJ 可能不接受的 RV64 asm 指令。
- 继续保持 `usize/isize` 为 64-bit，不能破坏 `w64tag`、`isW64Stack`、`ld/sd` 和 64-bit 运算语义。
- RV64 正确性验证必须用 qemu，不用 REIMU：

```bash
cmake --build build
bash /tmp/qemu_test.sh
bash /tmp/qt2.sh RCompiler-Testcases/long-param/src
```

- 每完成一个优化单独 commit。提交前至少跑：
  - `RCompiler-Testcases/long-param/src`
  - `RCompiler-Testcases/semantic-2/src`
  - `RCompiler-Testcases/semantic-1/src`

## 1. OJ 隐藏性能点画像

当前 OJ 优化性能点共 17 个：

### 1.1 最新 OJ 反馈

最新已知 OJ 反馈来自 `b231011 opt: tighten scalar memory inlining`，总分比 `d53bcc7` 略降。收紧 scalar-memory helper inline 是负优化：`sort_kmp`、`tree_hashmap`、`compression`、`inmemory` 下降，只有 `array`、`graph`、`string` 小幅上升。因此该调参已撤销，后续不继续沿“整体收紧 scalar-memory inline”方向推进。

随后对 LICM 做保守化处理：cheap binary hoist 只保留服务 `getptr` 地址链的 `add/sub`，不再通过 cast 或贵表达式链继续泛化传播，也不再提前 `and/or/xor`。目标是保留数组地址计算收益，同时减少解释器、hash pipeline、状态机类样例中的 live range 膨胀。

| 优先级 | Case | 当前得分 | 丢分 | 主要判断 |
|---|---|---:|---:|---|
| 1 | `opti_graph_algorithms_suite` | `3.27 / 8.00` | `4.73` | 图/邻接结构，地址计算、load/store 和寄存器压力 |
| 2 | `opti_ntt_convolution` | `2.76 / 6.00` | `3.24` | 模乘、`%`、循环内数组访问 |
| 3 | `opti_bytecode_vm_interpreter` | `2.69 / 6.00` | `3.31` | 解释器 dispatch、状态字段反复读写、分支和寄存器压力 |
| 4 | `opti_range_structures_suite` | `3.89 / 7.00` | `3.11` | 树状/区间结构，结构字段和数组访问 |
| 5 | `opti_inmemory_index_query` | `3.76 / 7.00` | `3.24` | 内存索引，结构体字段 alias 和 load forwarding |
| 6 | `opti_block_hash_pipeline` | `4.79 / 7.00` | `2.21` | block hash 长 pipeline，CSE 和 inline/LICM 可能增加寄存器压力 |

最近三项增强整体有收益，但 `opti_block_hash_pipeline` 从 `5.32` 降到 `4.90`，`opti_recursive_utility_pipeline`、`opti_dp_suite`、`opti_branch_state_machine` 也有小幅回退。优先怀疑 `69f5ec3` 的 `x * (2^k +/- 1)` 展开：RV64GC 中 `mul` 是单条指令，展开成 `slli + add/sub` 可能增加动态指令数和寄存器压力。

当前短期调整状态：

1. 已收紧 `near-power-of-two multiplies`，保留 `x * 2^k`、unsigned `/ % 2^k` 这类明确收益转换。
2. 已增强 MemoryForward 的结构体字段 alias 精度，覆盖同根路径中不同常量字段的 disjoint 判断。
3. 已在 LocalCSE 后重跑 MemoryForward/ConstantFold/CFGClean，让 getptr canonicalize 后的地址事实继续参与转发。
4. 已为 MemoryForward 增加 dominated load cache，覆盖 `load p; ...; load p` 且中间无别名写入的场景。
5. 已增强 LICM，并在 OJ 负反馈后收窄为只提前服务 getptr 地址链的 `add/sub` cheap binary。
6. 已做 boolean branch peephole，减少解释器/状态机中 `seqz/snez/slti + bnez` 形态的临时值。
7. 暂不做 `% const` 魔数除法/模乘 lowering；它通常需要 `mulh/mulhu` 或更复杂序列，先避免 OJ `CE_ASM` 风险。

`d53bcc7` 相对上一轮的 OJ delta：

- 明显提升：`opti_array_transform +0.47`、`opti_tree_hashmap_suite +0.27`、`opti_compression_match_finder +0.19`、`opti_graph_algorithms_suite +0.18`。
- 明显回退：`opti_bytecode_vm_interpreter -0.23`、`opti_inmemory_index_query -0.17`、`opti_struct_pool_fold -0.14`、`opti_block_hash_pipeline -0.11`。
- 判断：新增优化总体方向有效，但泛化的 inline / LICM / load reuse 可能在状态机和长 pipeline 上放大活跃区间。

`b231011` 相对 `d53bcc7` 的 OJ delta：

- 小幅提升：`opti_array_transform +0.06`、`opti_graph_algorithms_suite +0.06`、`opti_string_automata_suite +0.10`。
- 明显回退：`opti_sort_kmp_suite -0.22`、`opti_inmemory_index_query -0.14`、`opti_tree_hashmap_suite -0.14`、`opti_compression_match_finder -0.08`、`opti_struct_pool_fold -0.06`。
- 结论：收紧 scalar-memory inline 会伤害更多 case，撤销该调参；下一步优先验证收窄 LICM cheap binary hoist 后的 OJ 变化。

### 1.2 和 O1 差距最大的当前瓶颈

当前与 O1 的主要差距更像后端问题，而不是再缺一个单独的 IR pass。IR 层的 mem2reg、inline、CSE/GVN、MemoryForward、LICM、SCCP、SROA 已经覆盖基础优化；继续泛化 IR pass 很容易把 live range 拉长，使后端 spill 变多。

最高优先级瓶颈：

1. `LinearScan` 仍是单 live interval 模型，没有 live hole，也没有真正的 live range splitting。分支、循环和长 pipeline 会把短命临时拉成长活跃区间。
2. spill/reload 质量仍不接近 O1。当前只做了局部 cleanup，没有跨 block spill value forwarding，也没有 rematerialization。
3. copy coalescing 还不足。phi lowering、参数搬运、返回值搬运和 peephole 未覆盖的 `mv` 链会制造额外 live range。
4. 指令选择和地址模式还不够强。O1 会更稳定地把地址临时折入 `ld/st offset(base)`，并减少常量 materialize 和 getptr 临时。
5. call/frame 成本刚开始优化。实际参数 liveness、leaf frame、callee/caller saved 压力仍有空间。

这些瓶颈最影响：

- `opti_bytecode_vm_interpreter`
- `opti_graph_algorithms_suite`
- `opti_range_structures_suite`
- `opti_ntt_convolution`
- `opti_block_hash_pipeline`
- `opti_inmemory_index_query`

后续主线应集中在 B1/B2/B3：更准确的寄存器分配、更少 spill/reload、更强 copy coalescing。只有当后端内存流量明显下降后，再回头判断是否需要新的 IR loop/alias 优化。

| Case | 主要热点判断 | 优先优化方向 |
|---|---|---|
| `opti_compute_hash_mix` | hash 混合、整数表达式、数组访问 | GVN, load forwarding, LICM |
| `opti_recursive_utility_pipeline` | 小 helper、递归/调用链 | inline cost model, DCE, SCCP |
| `opti_array_transform` | 大数组循环 | getptr/load CSE, LICM, strength reduction |
| `opti_branch_state_machine` | 分支状态机 | SCCP, CFG clean, cross-block GVN |
| `opti_struct_pool_fold` | 结构池、字段访问 | SROA, alias-aware memory forwarding |
| `opti_range_structures_suite` | 树状/区间结构和数组 | load forwarding, loop CSE, LICM |
| `opti_graph_algorithms_suite` | 图算法、邻接结构 | getptr CSE, load forwarding, reg pressure |
| `opti_ntt_convolution` | 模乘、循环、数组 | LICM, strength reduction, CSE |
| `opti_dp_suite` | DP 数组和嵌套循环 | loop-aware CSE, load forwarding |
| `opti_sort_kmp_suite` | 排序/KMP，分支和数组 | getptr/load CSE, branch cleanup |
| `opti_string_automata_suite` | 自动机表、字符串数组 | load CSE, loop invariant table access |
| `opti_block_hash_pipeline` | 块 hash、长 pipeline | GVN, algebraic simplify, reg pressure |
| `opti_compression_match_finder` | 滑窗/匹配查找 | loop CSE, load forwarding, LICM |
| `opti_inmemory_index_query` | 内存索引查询 | alias-aware load forwarding, CSE |
| `opti_tree_hashmap_suite` | 树/hashmap 混合 | load forwarding, GVN, branch cleanup |
| `opti_bytecode_vm_interpreter` | 解释器 dispatch、状态读写 | load forwarding, branch cleanup, reg pressure |
| `opti_image_signal_kernel` | stencil/kernel 循环 | LICM, getptr CSE, strength reduction |

结论：

- `Global2Local` 不是当前优先级最高的优化。当前前端主要把顶层 `const` 折成 literal，IR 中没有稳定看到实际生成 `IRGlobal` 的路径。
- 隐藏点主要吃数组、结构体字段、循环、重复地址计算、重复 load、状态机分支和寄存器压力。

## 2. 当前已完成优化

当前已有并已接入的优化方向：

- `Mem2Reg`
- 支配树/SSA promotion
- function inline
- constant folding / algebraic simplification
- CFG clean
- IR DCE
- memory forwarding 初版
- alias-aware memory forwarding：
  - store-load forwarding
  - dead store elimination for same known location in one block
  - known-field disjoint alias check
  - dominated load reuse
- local CSE 初版，含 binary/getptr/load 的局部处理
- dominator-tree CSE/GVN for pure binary/getptr/cast and conservative load reuse
- LICM，含 expensive scalar/getptr/cast hoist，以及地址链 cheap binary hoist
- strength reduction，保留 power-of-two multiply and unsigned div/mod
- SROA 小范围版本，含 int/pointer scalar fields
- function inline cost model，含 scalar memory helper inline
- SCCP，含：
  - sparse executable edge propagation
  - phi 常量传播
  - branch 常量化
  - legacy bool phi folding
  - branch edge facts
  - `x == const` / `x != const` 的分支内事实传播
- 后端 peephole 和寄存器分配策略已有若干调整
- boolean branch peephole for common compare-to-zero forms
- post-regalloc spill cleanup：
  - redundant reload reuse
  - same-value spill store deletion
  - overwritten spill store deletion

当前后续优化不应重复做已完成的基础 pass。下一轮应先等 OJ 反馈，按 case 回归决定是否回滚或调参。

## 3. 下一阶段优先级

### P0: Loop-aware GetPtr/Load CSE

目标：减少热循环中的重复地址计算和重复 load。

状态：大部分已经由当前 dominator-tree `LocalCSE` 和 MemoryForward load cache 覆盖。后续只做 alias 精度和 pipeline 调度增强，不再另起一个重复 pass。

第一版保持保守：

- 在单个基本块内已经做过 local CSE，下一步扩展到 loop body 内的支配关系。
- 只复用纯 `IRGetptr`、`IRBinaryop`、cast。
- 对 `IRLoad` 只在以下条件下复用：
  - 地址 key 完全相同。
  - dominating load 到当前 use 之间没有 `IRStore`、`IRCall`、`IRGetint`、`IRMemcpy`、`IRMemset`。
  - 不跨 loop backedge 做不安全复用。
- 遇到未知 memory side effect 清空 load table。

适用隐藏点：

- `opti_array_transform`
- `opti_dp_suite`
- `opti_ntt_convolution`
- `opti_image_signal_kernel`
- `opti_graph_algorithms_suite`
- `opti_string_automata_suite`

风险：

- alias 不清楚时必须保守。
- 不能把 loop 上一次迭代的 load 错误复用到下一次迭代。

建议 commit：

```text
opt: extend cse across dominated blocks
```

### P1: LICM

目标：把循环不变量移出循环。

状态：已实现并增强。当前 hoist 范围是：

- profitable binary: `mul/div/mod/shift`
- pure getptr
- casts
- 服务于可提升 getptr 地址链的 cheap binary: `add/sub`

当前仍不 hoist load，避免内存 alias 误判。

实现步骤：

1. 构建 CFG 和 predecessor。
2. 利用现有支配信息或新增 helper 检测 natural loop：
   - back edge `b -> h`
   - `h` dominates `b`
3. 为 loop header 创建 preheader，或复用唯一外部 predecessor。
4. hoist 安全指令：
   - `IRBinaryop`
   - `IRSext` / `IRZext` / `IRTrunc`
   - 纯 `IRGetptr`
5. 暂不 hoist `IRLoad`，除非后续有更强 alias analysis。

可 hoist 条件：

- operands 定义在 loop 外，或来自已经 hoist 的 invariant。
- 指令无副作用。
- `DIV/MOD` 只在 divisor 是非零常量时 hoist。

适用隐藏点：

- `opti_ntt_convolution`
- `opti_image_signal_kernel`
- `opti_array_transform`
- `opti_compute_hash_mix`
- `opti_block_hash_pipeline`

风险：

- preheader 插入后必须维护 block 顺序和 phi predecessor。
- 不要 hoist 可能依赖内存变化的 load。

建议 commit：

```text
opt: hoist loop invariant scalar expressions
```

### P2: Alias-aware Memory Forwarding 增强

目标：让结构体池、数组局部更新和解释器状态变量少走内存。

状态：已完成当前安全版本。后续方向是继续提升地址规范化能力，尤其是把等价 getptr 链和相同动态 index 下的固定字段路径识别得更稳定。

在现有 `memoryForward` 基础上增强：

- 建立地址 key：
  - 直接 alloca/global var
  - `getptr(base, const index/type)` 的规范化 key
  - 已知等价 getptr 的 alias key
- 支持 dominated block 内 store-load forwarding：
  - `store v, p` dominates `load p`
  - 中间无 may-write memory side effect
- 支持 dead store elimination：
  - `store a, p; store b, p` 中间无 load/use/may-write，则删前一个 store
- 对 call/getint/memcpy/memset 保守清空。

适用隐藏点：

- `opti_struct_pool_fold`
- `opti_bytecode_vm_interpreter`
- `opti_inmemory_index_query`
- `opti_tree_hashmap_suite`
- `opti_compression_match_finder`

风险：

- 没有完整 alias analysis 时，只认精确同地址或明确等价地址。
- 对数组动态 index 不要跨未知 store 复用。

建议 commit：

```text
opt: forward memory across dominated blocks
```

### P3: Cross-block GVN

目标：跨基本块复用已支配的纯表达式。

状态：当前 `LocalCSE` 实际已按 dominator tree 向下传播 pure expression table，覆盖 binary/getptr/cast；后续重点是降低由表达式替换带来的寄存器压力，而不是新增重复 GVN pass。

范围：

- `IRBinaryop`
- cast
- `IRGetptr`
- 不包含 memory load，load 交给 P2。

实现：

- DFS dominator tree。
- 进入 block 时继承 value table。
- 离开 block 时回滚本 block 插入项。
- 对 commutative op 规范化左右操作数。

适用隐藏点：

- `opti_branch_state_machine`
- `opti_compute_hash_mix`
- `opti_block_hash_pipeline`
- `opti_recursive_utility_pipeline`

风险：

- 必须保证表达式纯且 flags 一致：`utag`、`i8tag`、`w64tag`、类型 key 都要进入 key。

建议 commit：

```text
opt: add dominator-based gvn for pure expressions
```

### P4: SROA 小范围版本

目标：拆小结构体字段或固定下标数组元素，减少结构体池和小对象内存访问。

状态：已完成当前安全版本。支持小 struct/fixed array 的 int/pointer scalar fields，支持 `memset 0` 和候选间 `memcpy` copy init。指针字段会保留 pointer-storage 栈槽语义。

第一版只做非常保守场景：

- 局部 alloca。
- 类型是小 struct 或小 fixed array。
- 地址不逃逸。
- 所有访问都是常量字段/常量 index。
- 不处理 dynamic index。
- 不处理作为参数传给函数的聚合地址。

转换：

- 每个字段/元素建独立 scalar alloca。
- 后续交给 mem2reg / dominantTree promotion。

适用隐藏点：

- `opti_struct_pool_fold`
- `opti_recursive_utility_pipeline`
- 小对象密集代码

风险：

- 聚合 memcpy/memset、by-value 参数和 return pointer 场景先跳过。

建议 commit：

```text
opt: scalarize simple aggregate locals
```

### P5: Function Inline Cost Model

目标：更贴近隐藏点里的 helper 函数调用。

状态：已完成当前安全版本。仍限制为无基本块、非递归、int/void 返回的小函数；已允许 scalar alloca/getptr/load/store helper inline，继续由 cost/growth budget 控制。

增强方向：

- 单调用小函数更激进 inline。
- 纯 getter/setter/算术 wrapper 优先 inline。
- long-param 或大聚合参数加惩罚，避免重新引入之前解释器点的寄存器压力问题。
- 对递归函数不 inline。
- 为 caller 设置 growth budget。

适用隐藏点：

- `opti_recursive_utility_pipeline`
- `opti_compute_hash_mix`
- `opti_block_hash_pipeline`

风险：

- inline 会放大寄存器压力；必须配合 DCE/SCCP/CFGClean。

建议 commit：

```text
opt: tune function inline cost model
```

### P6: Register Pressure 和 Spill Cleanup

目标：隐藏点里大型循环、解释器、图算法容易因为虚拟寄存器过多而 spill。

状态：已完成当前安全版本。post-regalloc peephole 已覆盖同块 redundant reload、same-value store、overwritten store cleanup，不新增 asm 指令。

IR 层优先：

- 减少无用临时。
- 合并 move chain。
- 不要过度 inline long-param 函数。

后端层保守增强：

- 继续使用当前支持的 RV64GC 指令，不新增 OJ 可疑指令。
- post-regalloc 局部 spill peephole：
  - `ld r, slot; sd r, slot` 删除 store。
  - `sd r, slot; ld r2, slot` 改 `mv r2, r`，中间无相关 clobber。
  - 连续 `ld` 同 slot 复用。

适用隐藏点：

- `opti_bytecode_vm_interpreter`
- `opti_graph_algorithms_suite`
- `opti_range_structures_suite`
- `opti_ntt_convolution`

风险：

- spill peephole 只做基本块内，不跨 label/call/branch。

建议 commit：

```text
opt: clean redundant spill reloads
```

## 4. 后端优化计划

IR 层已经覆盖了当前能安全做的大部分优化。下一阶段重点转到后端，目标不是新增激进指令，而是降低寄存器压力、减少 spill/reload、改进指令选择和清理冗余 asm。所有优化默认只使用当前已经输出过的 RV64GC/lp64d 指令形态，避免再次触发 OJ `CE_ASM`。

后端优化的核心判断：当前最接近 O1 差距的不是算术 strength reduction，而是寄存器分配质量和 spill 流量。即使 IR pass 减少了表达式数量，只要 allocator 把 live range 过度拉长，热点循环仍会被 `ld/sd` 吞掉收益。

### B0: 后端性能画像和统计

目标：先让后端瓶颈可见，避免继续盲目调 pass。

需要统计：

- 每个函数的 asm 指令数。
- `ld/sd` 总数，以及访问 `s0/sp` spill slot 的 `ld/sd` 数。
- 每个函数的虚拟寄存器数、分配到物理寄存器数、spill slot 数。
- prologue/epilogue 中保存恢复的 callee-saved 数。
- call 数、跨 call live interval 数。
- 大 frame 函数数量，以及 frame size 是否超过 12-bit offset。

实现方式：

- 在 debug flag 或临时本地脚本中统计，不影响默认 OJ 输出。
- 优先对比 17 个 OJ 隐藏点对应方向的本地 microbench：解释器、图、NTT、hash pipeline、数组循环。
- 每次后端优化后记录静态指标变化，再以 OJ 反馈为最终依据。

建议 commit：

```text
docs/tooling: add backend asm statistics
```

### B1: 改进 liveness 和 live interval 精度

目标：减少线性扫描把短生命周期虚拟寄存器错误拉成长区间造成的 spill。

当前风险点：

- `LinearScan` 目前用每个 vreg 的最小 start 和最大 end 形成单区间，不能表达 live hole。
- block 入口/出口 live set 会把 interval 扩到 block 边界，循环和分支较多时容易放大寄存器压力。
- `CALL` 当前按固定 caller-saved clobber 处理，但 call 的真实参数 use 和返回值 def 仍可进一步精确。

已完成子项：

- `CALL` 记录实际占用的 `a0-a7` 参数数，liveness 不再默认把所有 `a0-a7` 都视为 use。
- spill victim 改为参考下一次 use，而不是只比较 interval end。

第一阶段保守增强：

- 继续完善指令编号，区分 use-before-def 和 def-before-use。
- interval 继续记录 use positions，并用于更多 spill/reload 决策。
- 对没有后续 use 的 def 尽早交给 ASM DCE 删除，避免进入分配。

第二阶段增强：

- 支持 live range splitting 的轻量版：只在 spill 前后插入 reload/store，不把整个 vreg 固定成全函数 spill。
- 允许在 block 内切开长 interval，让短热点片段优先留在物理寄存器。
- 不做复杂 SSA-aware allocator，先保持现有 linear scan 框架。

适用隐藏点：

- `opti_bytecode_vm_interpreter`
- `opti_graph_algorithms_suite`
- `opti_ntt_convolution`
- `opti_block_hash_pipeline`
- `opti_range_structures_suite`

风险：

- liveness 错误会直接 WA，必须先用小函数、多分支、循环、call 的专门用例覆盖。
- call 边界必须严格遵守 RISC-V ABI：caller-saved 不能跨 call 假定保留。

建议 commit：

```text
opt: improve linear scan spill choice
```

### B2: Spill code 优化

目标：减少每条指令周围重复的 `ld/sd`。

当前已有：

- 同基本块内 redundant reload 复用。
- same-value spill store deletion。
- overwritten spill store deletion。
- 同一条指令内重复 use/def 的 spill rewrite 去重。

下一步增强：

- 在基本块内维护 `slot -> reg` 和 `reg -> slot` 状态，覆盖更多 `ld slot; ...; ld slot`，中间只要没有写同 slot 就复用。
- 对 `ld r, slot; op ... r ...; sd r, slot`，如果 vreg 值未改变则删除 store。
- 对连续 spill slot 访问尽量避免重复 materialize 大 offset 地址。
- 大 frame 时优先用 `s0` 稳定访问 frame slot，避免每次 `li + add + ld/sd`。
- 做轻量 rematerialization：常量 `li`、小 offset 地址、简单 `addi` 不一定要 spill slot，必要时重新生成可能更便宜。

不做：

- 不跨基本块做 spill value forwarding，除非后续有可靠的 CFG dataflow。
- 不新增压缩指令或 OJ 未确认指令。

适用隐藏点：

- `opti_bytecode_vm_interpreter`
- `opti_graph_algorithms_suite`
- `opti_range_structures_suite`
- `opti_inmemory_index_query`

建议 commit：

```text
opt: reduce redundant spill traffic
```

### B3: Copy coalescing 和 move 消除

目标：降低 `mv` 链和 move 引起的额外 live range。

当前已有：

- peephole 删除 self-move。
- 局部 `mv` 合并到下一条 use。

下一步增强：

- 分配前收集 `mv v1, v2`，如果两者 live interval 不冲突，优先分到同一物理寄存器。
- 对 phi lowering、call return、argument move 产生的 copy chain 做 coalescing。
- 对 `li tmp, imm; mv dst, tmp`、`mv tmp, src; op dst, tmp` 这类单 use 模式继续扩大 peephole。
- 保留 width 语义：涉及 `addw/subw`、显式 sign/zero extend 的 move 不能错误合并。

执行优先级：

- 先做非冲突 move coalescing，不改变 CFG。
- 再尝试把 call argument staging 产生的 `mv` 链缩短。
- 最后处理 phi/copy chain，避免一次改动过大。

适用隐藏点：

- `opti_recursive_utility_pipeline`
- `opti_branch_state_machine`
- `opti_bytecode_vm_interpreter`
- `opti_sort_kmp_suite`

建议 commit：

```text
opt: coalesce non-conflicting moves
```

### B4: 指令选择改进

目标：在不新增风险指令的前提下，减少明显多余的临时寄存器和指令数。

优先项：

- 更积极使用 12-bit immediate：
  - `add x, y, const` -> `addi`。
  - `and/or/xor` with 12-bit const -> 对应 immediate 指令。
  - compare with small const -> `slti/sltiu`。
- load/store 地址选择：
  - `addi addr, base, off; ld/st ..., 0(addr)` 合并为 `ld/st ..., off(base)`。
  - getptr 常量偏移尽量延迟到 load/store offset。
  - 大 offset 只 materialize 一次，避免每个访问都 `li + add`。
- branch 选择：
  - 已有 compare+branch peephole，继续覆盖 `xori bool, 1; bnez`、`seqz/snez` 的反向分支。
  - 删除跳到下一块的无条件 `j`。
- return path：
  - 小函数单出口保留统一 epilogue；多 return 函数避免生成过长跳转链。

风险：

- 32-bit 和 64-bit 运算不能混淆。`usize/isize` 必须继续保持 64-bit。
- pseudo `li/mv` 当前已在用，可以继续用；不要引入 OJ 未确认的 pseudo。

适用隐藏点：

- `opti_compute_hash_mix`
- `opti_array_transform`
- `opti_ntt_convolution`
- `opti_image_signal_kernel`

建议 commit：

```text
opt: select immediate forms in backend
```

### B5: Call/ABI 和栈帧优化

目标：降低函数调用和栈帧维护成本，同时保持 ABI 正确。

优先项：

- 精确 call 参数 use：只把实际传参用到的 `a0-a7` 计入 use，避免所有 call 都把 `a0-a7` 拉进 liveness。
- 精确 call 返回 def：只在有返回值时认为 `a0` 被定义。
- leaf function 不保存 `ra`，没有使用 `s0` frame pointer 时考虑省略 `s0` 保存和设置。
- 只保存实际分配到的 callee-saved，当前已有基础逻辑，继续检查大函数下是否过度使用 callee-saved。
- 对没有 alloca、没有 spill、没有 call 的函数生成最小 frame 或无 frame。

风险：

- OJ runtime 和 gcc 链接遵守标准 ABI，任何 call-saved/caller-saved 误判都会 WA。
- 省略 frame pointer 需要确认所有栈槽 offset 都能稳定基于 `sp` 表达；否则先只做 leaf/no-spill/no-alloca 的安全子集。

适用隐藏点：

- `opti_recursive_utility_pipeline`
- `opti_compute_hash_mix`
- `opti_sort_kmp_suite`
- `opti_branch_state_machine`

建议 commit：

```text
opt: reduce unnecessary stack frame work
```

### B6: 块布局和跳转清理

目标：降低分支和跳转开销。

当前已有：

- post-regalloc peephole 可删除跳到下一块的 fallthrough jump。
- leaf function 已跳过 `ra` save/restore，仍保留 `s0` frame base 以维持当前栈槽访问逻辑。

下一步增强：

- 按 CFG 调整 block 顺序，使 hot-looking fallthrough 更自然。没有 profile 时优先：
  - loop backedge 仍保留跳转，loop body 顺序连续。
  - if-else 中让非 exit 分支 fallthrough。
  - exit/return block 放后面。
- 合并只有一个 predecessor、一个 successor 的空 block。
- 删除 `j L1; L1:`、`bnez x, L1; j L2; L1:` 可安全反转时的跳转。

风险：

- 改 block 顺序不能破坏 label 和 branch target。
- 没有 profile 时只做结构性优化，不做猜测性大重排。

适用隐藏点：

- `opti_branch_state_machine`
- `opti_bytecode_vm_interpreter`
- `opti_string_automata_suite`

建议 commit：

```text
opt: clean backend control flow
```

### B7: 后端优化执行顺序

推荐顺序：

1. B0 统计和样例画像。
2. B1 live interval / spill 选择 / 轻量 live range splitting。
3. B2 spill traffic 清理和 rematerialization。
4. B3 copy coalescing。
5. B4 immediate/address 指令选择。
6. B5 call/frame 优化。
7. B6 block layout 和跳转清理。

每完成一步都按单 commit 提交，并跑：

```bash
cmake --build build
bash /tmp/qt2.sh RCompiler-Testcases/long-param/src
bash /tmp/qemu_test.sh
```

如果 `/tmp` 脚本不存在，用等价 qemu 流程跑 `semantic-2` 和 `long-param`。semantic-1 继续按 `global.json` 的 `compileexitcode` oracle 跑 222 个样例。

## 5. Global2Local 位置

`Global2Local` 暂时放低优先级。

原因：

- 当前代码中 `IRGlobal` 类型存在，但没有稳定看到实际生成 `IRGlobal` 的路径。
- 顶层 `const` 已经由前端/IRBuilder 直接折成 literal。
- OJ 隐藏点更像数组、循环、结构池和状态机热点，不像全局变量访问热点。

如果未来要做，第一版只处理：

- 标量 global/static。
- 只被单个函数使用。
- 地址不逃逸。
- 所有 use 都是直接 load/store。
- 在该函数入口创建 local alloca + 初始 store。
- 删除 `IRGlobal`，后续交给 mem2reg。

建议放在：

```text
Global2Local -> Mem2Reg -> DominantTree
```

但当前不作为下一步任务。

## 6. 建议后续顺序

已完成或已有等价实现：

1. Loop-aware getptr/load CSE
2. LICM
3. Alias-aware memory forwarding
4. Cross-block GVN
5. SROA 小范围版本增强
6. Inline cost model 调优
7. Spill/reload cleanup

短期后续优先级：

1. 后续主线转到后端优化，先做 B0 后端统计，确认 spill、frame、call、branch 的真实占比。
2. 按 B1-B6 顺序推进：先改 linear scan spill 选择和 interval 精度，再做 spill traffic、copy coalescing、指令选择、call/frame、block layout。
3. 每个后端优化单独 commit，提交 OJ 后记录 17 个隐藏点变化；若出现负优化，按单 commit 回滚或收窄。
4. IR 层后续只做有明确 case 证据的小修，不再继续泛化堆 pass。

如果 OJ 分数仍不理想，再做：

5. 更激进的 loop strength reduction，但需要警惕寄存器压力和 `CE_ASM`。
6. 多 block inline。
7. Global2Local。

## 7. 当前推荐管线

当前实际管线：

```text
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
Peephole
ASM DCE
LinearScan
Peephole
ASMPrinter
```

说明：

- `FunctionInline` 后最好重新跑支配/SSA 或至少确认后续 pass 不依赖过期 CFG。
- `LocalCSE` 后重跑 `MemoryForward` 是有意安排：getptr/address 经过 CSE 后，load/store 转发能看到更多等价地址。
- `LICM` 放在第二轮 MemoryForward/CFGClean 后，避免提升已经能被转发/折叠掉的临时。
- `MemoryForward` 后常会制造常量和死 load/store，应接 `ConstantFold/CFGClean/DCE`。
- 后端后续优化集中在 `ASM DCE -> LinearScan -> Peephole` 这一段，优先降低 spill/reload 和 frame 成本。

## 8. 验证策略

正确性：

```bash
cmake --build build
bash /tmp/qt2.sh RCompiler-Testcases/long-param/src
bash /tmp/qemu_test.sh
```

semantic-1 需要按 `Verdict:` 字段检查 222 个样例。

性能代理指标：

- 本地 semantic-2 汇编行数只作为 sanity check，不代表 OJ 优化分。
- 对本地构造的 loop/hash/array/struct microbench，记录：
  - 编译是否成功
  - RV64 asm 是否能过 `riscv64-linux-gnu-gcc -static`
  - qemu 输出一致
  - 指令数/汇编行数是否下降

OJ 隐藏点反馈优先级最高。每次 OJ 后记录：

- 哪些 case 提升。
- 哪些 case 下降。
- 是否出现 CE/WA/CE_ASM。
- 本次 pass 是否可能导致寄存器压力上升或代码体积膨胀。

## 9. 风险清单

- 所有 memory 优化必须保守处理 alias。遇到 call/getint/memcpy/memset/未知 store 时清空相关状态。
- 循环优化不能把本轮迭代的 load 复用到下一轮迭代。
- CFG 修改必须同步 phi predecessor。
- `usize/isize` folding 和替换必须保留 64-bit 语义。
- `addw/subw` 的 32-bit sign-extension 语义不能被普通 `mv/add` 错误替代。
- Inline 调优不能重新制造解释器 hidden case 的巨大寄存器压力。
- 后端不新增未经 OJ 验证的伪指令或扩展指令。
