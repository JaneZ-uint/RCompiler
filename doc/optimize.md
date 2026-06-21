# RCompiler Optimization Plan

本文档记录下一阶段优化方向。`semantic-1`、`semantic-2`、`long-param` 只作为正确性回归集；优化收益以 OJ 的 17 个隐藏性能点为主，不再用 `semantic-2` 的静态汇编变化判断总体收益。

## 0. 当前约束

- 只做 IR 层和现有后端指令内的优化，暂时不要新增 OJ 可能不接受的 RV64 asm 指令。
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

最新提交到 `69f5ec3 opt: reduce near-power-of-two multiplies` 后，OJ 总分约 `60.24 / 100`。当前丢分主要集中在数据结构、NTT 和解释器类隐藏点：

| 优先级 | Case | 当前得分 | 丢分 | 主要判断 |
|---|---|---:|---:|---|
| 1 | `opti_graph_algorithms_suite` | `3.09 / 8.00` | `4.91` | 图/邻接结构，地址计算、load/store 和寄存器压力 |
| 2 | `opti_ntt_convolution` | `2.75 / 6.00` | `3.25` | 模乘、`%`、循环内数组访问 |
| 3 | `opti_range_structures_suite` | `3.85 / 7.00` | `3.15` | 树状/区间结构，结构字段和数组访问 |
| 4 | `opti_bytecode_vm_interpreter` | `2.92 / 6.00` | `3.08` | 解释器 dispatch、状态字段反复读写、分支 |
| 5 | `opti_inmemory_index_query` | `3.93 / 7.00` | `3.07` | 内存索引，结构体字段 alias 和 load forwarding |
| 6 | `opti_tree_hashmap_suite` | `3.99 / 7.00` | `3.01` | tree/hashmap 混合，load forwarding、CSE、spill |

最近三项增强整体有收益，但 `opti_block_hash_pipeline` 从 `5.32` 降到 `4.90`，`opti_recursive_utility_pipeline`、`opti_dp_suite`、`opti_branch_state_machine` 也有小幅回退。优先怀疑 `69f5ec3` 的 `x * (2^k +/- 1)` 展开：RV64GC 中 `mul` 是单条指令，展开成 `slli + add/sub` 可能增加动态指令数和寄存器压力。

当前短期调整：

1. 先收紧或回滚 `near-power-of-two multiplies`，只保留明确收益的乘法 strength reduction。
2. 增强 MemoryForward 的结构体字段 alias 精度，重点覆盖 `a[i].x` 和 `a[i].y`、同根不同常量字段的 disjoint 判断。
3. 针对 `opti_ntt_convolution`，优先寻找不增加新 ASM 的 `% const`、模乘、循环不变量优化。
4. 针对 `opti_bytecode_vm_interpreter`，优先减少循环内状态字段的重复 load/store 和无谓 spill。

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
- local CSE 初版，含 binary/getptr/load 的局部处理
- SCCP，含：
  - sparse executable edge propagation
  - phi 常量传播
  - branch 常量化
  - legacy bool phi folding
  - branch edge facts
  - `x == const` / `x != const` 的分支内事实传播
- 后端 peephole 和寄存器分配策略已有若干调整

当前后续优化不应重复做已完成的基础 pass，而应围绕隐藏点继续增强内存、循环和跨块表达式能力。

## 3. 下一阶段优先级

### P0: Loop-aware GetPtr/Load CSE

目标：减少热循环中的重复地址计算和重复 load。

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

## 4. Global2Local 位置

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

## 5. 建议后续顺序

短期优先完成：

1. Loop-aware getptr/load CSE
2. LICM
3. Alias-aware memory forwarding
4. Cross-block GVN
5. SROA 小范围版本

如果 OJ 分数仍不理想，再做：

6. Inline cost model 调优
7. Spill/reload cleanup
8. 更激进的 loop strength reduction
9. 多 block inline
10. Global2Local

## 6. 当前推荐管线

当前实际管线应保持类似：

```text
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
LocalCSE
DCE
InstrSelect
Peephole
ASM DCE
LinearScan
Peephole
ASMPrinter
```

新增循环/GVN/memory pass 后建议变为：

```text
Mem2Reg
DominantTree
SCCP
FunctionInline
DominantTree
SCCP
CFGClean
DCE
CrossBlockGVN
LoopCSE
LICM
MemoryForward
ConstantFold
SCCP
CFGClean
DCE
LocalCSE
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
- `LICM/GVN/LoopCSE` 依赖干净 CFG 和支配关系，放在 `CFGClean/DCE` 后更稳。
- `MemoryForward` 后常会制造常量和死 load/store，应接 `ConstantFold/SCCP/CFGClean/DCE`。

## 7. 验证策略

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

## 8. 风险清单

- 所有 memory 优化必须保守处理 alias。遇到 call/getint/memcpy/memset/未知 store 时清空相关状态。
- 循环优化不能把本轮迭代的 load 复用到下一轮迭代。
- CFG 修改必须同步 phi predecessor。
- `usize/isize` folding 和替换必须保留 64-bit 语义。
- `addw/subw` 的 32-bit sign-extension 语义不能被普通 `mv/add` 错误替代。
- Inline 调优不能重新制造解释器 hidden case 的巨大寄存器压力。
- 后端不新增未经 OJ 验证的伪指令或扩展指令。
