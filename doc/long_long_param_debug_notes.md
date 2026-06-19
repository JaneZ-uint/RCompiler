# Long Long Param Debug Notes

Date: 2026-06-20

This document records the recent `looooong looooong param` investigation. The hidden OJ case still fails after the latest fix, so this is mainly a handoff note to avoid repeating already tested directions.

## Current Ground Rules

- Use RV64 only:
  - compile generated asm with `riscv64-linux-gnu-gcc -static`
  - run with `qemu-riscv64`
- Do not use REIMU for generated RV64 asm.
- OJ output protocol still matters:
  - compiler stdout: user asm
  - compiler stderr: builtin runtime asm
  - concatenate stdout then stderr before assembling.

## Latest Committed Fix

Commit:

```text
eca306f fix: preserve nested reference args in calls
```

Problem fixed:

- Function calls with pointer parameters used to always pass `valueFromPtrStorage(arg)`.
- For an argument like `p: & &mut T` forwarded to another function expecting `& &mut T`, this loaded one level too far.
- The callee then treated an inner `&mut T` as if it were the outer `& &mut T`, so `**p` could read/write through a wrong address.

The fix added `pointerCallArg()` in `src/ir/IRBuilder.h`:

- If the argument is already the outer reference address and its shape matches the expected pointer base type, pass it directly.
- Otherwise keep the old `valueFromPtrStorage()` behavior.
- Applied to both normal calls and method calls.

Regression tests committed with that fix:

- `local_tests/inner_mut_ref_min.rx`
- `local_tests/inner_mut_ref_forward_min.rx`
- `local_tests/long_param_inner_mut_ref_matrix.rx`
- `local_tests/long_param_inner_mut_ref_forward_sret.rx`
- `local_tests/long_param_ref_array_matrix.rx`
- `local_tests/long_param_ref_array_forward_repeat.rx`
- `local_tests/long_param_ref_array_method_sret.rx`

Validation after the commit:

- `cmake --build build`: pass
- `local_tests/*.rx` positive tests at that time: pass
- `bash /tmp/qt2.sh RCompiler-Testcases/long-param/src`: `PASS=34 FAIL=0`
- semantic-2 manually with RV64/qemu: `PASS=50 FAIL=0`
- semantic-1 with `Verdict: Pass/Fail`: `PASS=222 FAIL=0`

## Function Parameter Type Checklist Added To AGENTS.md

Added a function-parameter checklist to `AGENTS.md`, covering:

- scalar params: `i32`, `u32`, `isize`, `usize`, `bool`
- user path types: struct, enum if supported by spec, `Self`
- references: `&T`, `&mut T`, multi-level references
- arrays: `[T; N]`, recursively combined with structs/references/scalars/bool
- method self forms
- parameter patterns
- explicitly excluded unsupported Rust-only types like `char`, `String`, tuple, slice, raw pointer, function pointer, generics/lifetimes

## Directions Tested After Commit

These were tested after `eca306f`. They did not reproduce the hidden failure.

### 1. Arrays Whose Elements Are References

Goal:

- Check `[&T; N]` and `[&mut T; N]` in long parameter lists.

Tests:

- `local_tests/long_param_ref_array_matrix.rx`
- `local_tests/long_param_ref_array_forward_repeat.rx`
- `local_tests/long_param_ref_array_method_sret.rx`

Covered:

- `[&i32; N]`, `[&mut i32; N]`
- `[&u32; N]`, `[&mut u32; N]`
- `[&isize; N]`, `[&mut isize; N]`
- `[&bool; N]`, `[&mut bool; N]`
- `[&Struct; N]`, `[&mut Struct; N]`
- `[&[usize; N]; M]`, `[&mut [usize; N]; M]`
- repeat-init of reference arrays
- `middle -> leaf` forwarding
- method call plus struct hidden return pointer

Result:

- All passed.

### 2. Inner Mutable Multi-Level References At Large Scale

Goal:

- Take the fixed `& &mut T` / `&mut &mut T` path and scale it to hidden-test size.

Generated local tests:

- `local_tests/long_long_inner_mut_refs_256.rx`
- `local_tests/long_long_inner_mut_refs_1024.rx`
- `local_tests/long_long_inner_mut_refs_4096.rx`
- `local_tests/long_long_inner_mut_refs_16384.rx`
- `local_tests/long_long_inner_mut_refs_dense_unique_1024.rx`

Covered:

- `& &mut usize/i32/u32/isize/bool/Pair/[usize; 3]`
- `&mut &mut usize/i32/u32/isize/bool/Pair/[usize; 3]`
- `middle -> leaf` forwarding
- selected ABI boundary positions: `8/9/15/16/31/32/.../16383`
- dense 1024-parameter version where every nested-reference parameter is actually read/written

Results:

- 256: output `1`
- 1024: output `1`
- 4096: output `1`
- 16384: output `1`
- dense unique 1024: output `1`

Note:

- A first dense test reused the same backing variables and output `344`; that was a test-generation issue, not a compiler result. The independent-backing-variable version passed.

### 3. By-Value Aggregate Forwarding Alias/Copy

Goal:

- Check whether `Struct` / `[T; N]` by-value parameters are incorrectly aliased when forwarded through `middle -> leaf`.

Generated local tests:

- `local_tests/byvalue_aggregate_forward_alias_min.rx`
- `local_tests/byvalue_aggregate_modify_then_forward.rx`
- `local_tests/long_param_byvalue_aggregate_forward_alias_512.rx`
- `local_tests/long_param_byvalue_aggregate_forward_alias_2048.rx`

Covered:

- `Pack` struct by value
- `[usize; 3]` by value
- nested `Big { Pack, [usize; 3], bool }`
- `middle` forwards by-value aggregate params to `leaf`
- `leaf` mutates its own by-value params
- `middle` then checks its own params remain unmodified
- `middle` mutates its own params first, then forwards; `leaf` should see the updated by-value content but not pollute `middle`

Results:

- min: output `31`
- modify-then-forward: output `255`
- 512: output `1`
- 2048: output `1`

### 4. Nested Calls As Long-Parameter Arguments

Goal:

- Check whether a nested call used as an outer call argument overwrites already-staged outgoing stack arguments.

Generated local tests:

- `local_tests/nested_call_stack_arg_overwrite_min.rx`
- `local_tests/nested_call_stack_arg_aggregate_mix.rx`
- `local_tests/nested_call_many_long_stack_args_512.rx`
- `local_tests/nested_call_side_effect_stack_args.rx`

Covered:

- outer call has stack arguments
- later outer arguments include nested calls
- nested calls themselves have stack arguments
- nested calls returning scalar, struct, and array
- multiple nested calls across a 512-argument outer call
- side-effect nested call mutating `&mut usize`, checking argument evaluation order

Results:

- min: output `65535`
- aggregate mix: output `262143`
- many 512: output `1`
- side-effect: output `65535`

### 5. Method Self Plus Hidden Return Pointer

Goal:

- Check ABI indexing when `self` and hidden return pointer shift the user-parameter boundary.

Generated temporary tests in `/tmp`:

- `/tmp/method_self_sret_long_512.rx`
- `/tmp/method_self_sret_long_2048.rx`
- `/tmp/method_self_array_sret_long_4096.rx`

Covered:

- `&self`
- `self: &Self`
- `mut self: Self`
- `&mut self`
- `self: &mut Self`
- methods returning struct
- methods returning array
- 512/2048/4096 mixed parameters

Results:

- 512 struct sret: output `1`
- 2048 struct sret: output `1`
- 4096 array sret: output `1`

These files were intentionally kept in `/tmp` and not added to the repo.

### 6. Parameter Patterns In Long Lists

Goal:

- Test semantic-valid parameter patterns in long parameter lists.
- Avoid patterns known to cause semantic aborts, because the hidden case reports WA, not CE/parser failure.

Generated temporary tests in `/tmp`:

- `/tmp/long_pattern_mix_1024.rx`
- `/tmp/long_pattern_mix_4096.rx`
- `/tmp/refmut_pattern_alias_check.rx`

Covered:

- `ref x: usize`
- `ref mut x: usize`
- `ref b: bool`
- `ref p: Pair`
- `ref arr: [usize; 3]`
- `&x: &usize`
- `&mut x: &mut usize`
- `&&x: & &usize`
- `&&p: & &Pair`
- `&&arr: & &[usize; 3]`
- wildcard `_`

Results:

- 1024: output `1`
- 4096: output `1`
- ref-mut alias check: output `63`

Known caveat:

- More deeply nested reference patterns have incomplete semantic handling in `NameResolver` and can CE/abort.
- Since the hidden result is WA, those are lower priority unless OJ reports change.

## Current Worktree State

At the time this note was written, the worktree still had unrelated benchmark deletions not made by this investigation:

```text
 D benchmark/benchmark_2026-06-13_01-40-26.txt
 D benchmark/benchmark_2026-06-13_18-54-38.txt
 D benchmark/benchmark_2026-06-13_18-56-22.txt
```

Do not accidentally stage those unless the user explicitly asks.

There are also several untracked generated local tests under `local_tests/` from the later investigation. They were not committed after `eca306f`.

## Current Best Next Direction

The highest-priority remaining direction is full-use long parameter lists:

- Previous generated tests often checked selected boundary parameters.
- Hidden may use every parameter, forcing much heavier:
  - function-entry parameter save slots
  - alloca frame size
  - stack offset materialization
  - register allocation and spills
  - bool/usize mixed width handling

Recommended next tests:

1. 4096 and 8192 parameters where every parameter contributes to the result.
2. Mixed repeating pattern:
   - `i32`
   - `u32`
   - `isize`
   - `usize`
   - `bool`
   - `&usize`
   - `&mut usize`
   - small struct by value
   - small array by value
   - struct with bool and usize fields
3. Make the callee read every parameter exactly once, preferably with simple additions/conditionals to keep expression complexity moderate.
4. Include a forwarding variant:
   - `middle(all params) -> leaf(all params)`
5. Include a bool-heavy variant:
   - many bool scalar params
   - `[bool; N]`
   - struct bool fields
   - `&bool`, `&mut bool`

Rationale:

- If hidden is still `long long param`, the remaining likely failure is not a missing exotic type shape, but pressure from full use of all arguments and large stack frames.

## Full-Use Mixed Long Parameter Step

Date: 2026-06-20

Goal:

- Convert the previous "selected boundary parameter" idea into a test where every parameter is read and contributes to the final answer.
- Keep expression complexity moderate so the test still mainly targets function parameter lowering, forwarding, stack arguments, and aggregate argument layout.

Generated tests:

- `local_tests/long_param_full_use_mix_4096.rx`
  - 4096 explicit parameters.
  - 16722 lines.
  - Expected score: `5732`.
  - RV64/qemu result: output `1`.
- `local_tests/long_param_full_use_mix_8192.rx`
  - 8192 explicit parameters.
  - 33415 lines.
  - Expected score: `11468`.
  - Not committed in this step: `./build/RCompiler` stayed in the front-end/codegen stage for more than ten minutes and produced an empty asm file before the run was manually terminated.

Parameter pattern used in the repeating cycle:

- `i32`
- `u32`
- `isize`
- `usize`
- `bool`
- `&usize`
- `&mut usize`
- `Pair` by value, where `Pair` contains `usize`, `i32`, and `bool`
- `[usize; 3]` by value
- `Boxy` by value, where `Boxy` contains `Pair`, `[usize; 3]`, and `bool`

Test shape:

- `main` constructs all arguments.
- `middle` receives all arguments and forwards all of them to `leaf`.
- `leaf` checks every argument.
- `&mut usize` parameters are mutated before being checked, so the test also covers write-through reference arguments across a long forwarding call.

Result:

- The 4096-parameter full-use mixed case passes.
- This reduces the likelihood that the remaining OJ `long long param` WA is caused by ordinary mixed scalar/reference/aggregate parameters that are all consumed once.
- The 8192 case exposed compile-time scalability pressure in RCompiler, but it did not produce a runtime WA signal.

Next high-priority directions:

- Try a smaller scale ladder between 4096 and 8192, for example 5120, 6144, and 7168, with command-level timeouts.
- Build a bool-heavy full-use variant with `bool`, `&bool`, `&mut bool`, `[bool; N]`, and structs with many bool fields.
- Build a larger aggregate-heavy variant where stack arguments are dominated by by-value structs and arrays, not scalar/reference arguments.

## Full-Use Mixed Scale Ladder: 5120

Date: 2026-06-20

Goal:

- Check whether the full-use mixed parameter test has a scale threshold immediately above the verified 4096 case.
- Keep the shape identical to `local_tests/long_param_full_use_mix_4096.rx` so the only intended variable is parameter count.

Generated test:

- `local_tests/long_param_full_use_mix_5120.rx`
  - 5120 explicit parameters.
  - 20429 lines.
  - Expected score: `7168`.
  - Same repeating parameter cycle as the 4096 test:
    - `i32`, `u32`, `isize`, `usize`, `bool`
    - `&usize`, `&mut usize`
    - `Pair`, `[usize; 3]`, `Boxy`
  - Same `main -> middle -> leaf` full-forwarding shape.
  - Every parameter is checked in `leaf`; `&mut usize` parameters are mutated then checked.

Command used:

```bash
timeout 300s ./build/RCompiler < local_tests/long_param_full_use_mix_5120.rx > /tmp/full_use_5120.s 2> /tmp/full_use_5120_builtin.s
```

Result:

- `timeout` returned `124`.
- `./build/RCompiler` did not finish within 300 seconds.
- No RV64 GCC/qemu result was produced because no complete asm was available.
- This is not evidence of a runtime WA; it is evidence that this specific full-use/full-forwarding generator becomes too expensive for local iteration somewhere between 4096 and 5120 parameters.

Implication:

- Ordinary full-use mixed scalar/reference/aggregate parameters are still not reproducing the hidden `long long param` WA at the largest locally verified size.
- Pushing this exact generator larger is low value unless investigating compile-time scalability itself.

Next better directions:

- Bool-heavy long parameter lists:
  - scalar `bool`
  - `&bool`
  - `&mut bool`
  - `[bool; N]`
  - structs with many bool fields mixed with `usize`
- Aggregate-heavy long parameter lists:
  - more by-value structs and arrays after the ABI register boundary
  - arrays of structs by value
  - structs containing arrays of references
- If continuing the scale ladder, try 4352, 4608, and 4864 with timeouts before 5120.

## Bool-Heavy Long Parameter Step

Date: 2026-06-20

Goal:

- Cover long parameter lists dominated by `bool` and bool-containing aggregates.
- Exercise `bool` together with references, mutable references, arrays, structs, and `usize` fields.
- Keep every parameter used, and include a `middle -> leaf` forwarding call so stack argument forwarding is still tested.

Small probes:

- `/tmp/bool_ref_probe.rx`
  - Covered `bool`, `&bool`, `&mut bool`, `BoolPack` by value, `&BoolPack`, and `usize`.
  - RV64/qemu output: `1`.
- `/tmp/bool_array_repeat_probe.rx`
  - Covered `[bool; 4]` with repeat init `[true; 4]`.
  - RV64/qemu output: `1`.
- `/tmp/bool_heavy_probe.rx`
  - Tried explicit bool array literal `[true, false, true, false]`.
  - `./build/RCompiler` aborted with `Wrong in expr array parsing,type mismatch.`
  - Therefore long bool-array tests currently use repeat-init (`[true; 5]` / `[false; 5]`) instead of explicit mixed bool array literals.

Generated long tests:

- `local_tests/long_param_bool_heavy_2048.rx`
  - 2048 explicit parameters.
  - 9827 lines.
  - Expected score: `3840`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_bool_heavy_3072.rx`
  - 3072 explicit parameters.
  - 14725 lines.
  - Expected score: `5760`.
  - RV64/qemu output: `1`.

Repeating parameter cycle:

- `bool`
- `&bool`
- `&mut bool`
- `[bool; 5]` by value, using repeat-init
- `Flags` by value, where `Flags` has four bool fields and one `usize`
- `&Flags`
- `usize`
- `&usize`

Result:

- Both 2048 and 3072 bool-heavy full-use/full-forwarding cases pass.
- This lowers the priority of ordinary bool scalar/reference/aggregate combinations as the remaining hidden `long long param` WA cause.
- The explicit bool array literal abort is a real uncovered implementation gap, but it would usually show as CE/RE rather than the reported hidden WA.

Next better direction:

- Aggregate-heavy long parameters:
  - more by-value structs and arrays after the ABI register boundary
  - arrays of structs by value
  - structs containing arrays of references
  - nested arrays such as `[[usize; 2]; 3]` and arrays of small structs

## Aggregate-Heavy Long Parameter Step

Date: 2026-06-20

Goal:

- Cover long parameter lists dominated by by-value aggregates instead of scalar/reference arguments.
- Put large aggregate arguments far past the ABI register boundary so they must use stack argument passing.
- Exercise nested aggregate shapes that previously looked under-covered.

Small probe:

- `/tmp/aggregate_heavy_probe.rx`
  - Covered:
    - `Pair` by value.
    - `[Pair; 2]` by value.
    - `Agg` by value.
    - `&Agg`.
    - `RefPack` inside `Agg`, with `&usize`, `&mut usize`, and `[bool; 3]` fields.
    - nested matrix `[[usize; 2]; 2]`.
  - RV64/qemu output: `1`.

Generated long tests:

- `local_tests/long_param_aggregate_heavy_1024.rx`
  - 1024 explicit parameters.
  - 6887 lines.
  - Expected score: `3200`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_aggregate_heavy_1536.rx`
  - 1536 explicit parameters.
  - 10308 lines.
  - Expected score: `4800`.
  - RV64/qemu output: `1`.

Repeating parameter cycle:

- `Pair`
- `[Pair; 2]`
- `Agg`
- `&Agg`
- `[[usize; 2]; 2]`
- `RefPack`
- `[usize; 4]`
- `usize`

Important aggregate definitions:

- `Pair` contains `usize`, `i32`, and `bool`.
- `RefPack` contains `&usize`, `&mut usize`, and `[bool; 3]`.
- `Agg` contains:
  - `Pair`
  - `[usize; 3]`
  - `[Pair; 2]`
  - `RefPack`
  - `[[usize; 2]; 2]`

Test shape:

- `main` constructs all arguments.
- `middle` receives all arguments and forwards every parameter to `leaf`.
- `leaf` reads every parameter.
- Mutable references inside aggregate fields are mutated and checked.

Result:

- Both aggregate-heavy cases pass.
- This lowers the priority of ordinary by-value aggregate stack passing, arrays of structs, structs with reference fields, and nested arrays as the remaining `long long param` WA cause.
- No code fix was made in this step.

Next better directions:

- Method long-parameter variants where `self` or `&mut self` shifts the ABI argument boundary together with aggregate parameters.
- Sret plus long aggregate parameters, where the hidden return pointer shifts all user arguments.
- Parameter destructuring patterns mixed with aggregate-heavy values rather than only scalar/reference values.

## Method Self Plus Sret Long Parameter Step

Date: 2026-06-20

Goal:

- Cover method calls where implicit `self` shifts the ABI argument boundary.
- Combine that with a non-scalar return value so the hidden sret return pointer also shifts user arguments.
- Keep the parameter list long and mixed, but still normal and spec-aligned.

Generated long tests:

- `local_tests/long_param_method_sret_mix_768.rx`
  - Method receiver: `&mut self`.
  - Return type: `Ret { score: usize, tail: [usize; 3], ok: bool }`.
  - 768 explicit user parameters, not counting implicit `self` or hidden sret pointer.
  - Expected score: `1253`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_method_sret_mix_1536.rx`
  - Same shape as the 768 case.
  - 1536 explicit user parameters.
  - Expected score: `2405`.
  - RV64/qemu output: `1`.

Repeating user parameter cycle:

- `i32`
- `usize`
- `bool`
- `Pair`
- `&Pair`
- `[usize; 3]`
- `&[usize; 3]`
- `&mut usize`

Test shape:

- `main` constructs a mutable `Host`.
- `host.run(...)` mutates `self.calls`.
- The method reads every parameter.
- `&mut usize` parameters are mutated and checked.
- The method returns a `Ret` aggregate containing the final score and fields derived from `self`.

Result:

- Both method+sret long-parameter cases pass.
- This lowers the priority of the basic `&mut self` + hidden return pointer boundary-shift scenario.

Next better directions:

- Parameter destructuring patterns mixed with aggregate-heavy values in a long parameter list.
- Associated function sret with long parameters, without a method receiver, to isolate hidden return pointer behavior.
- Larger `self` by-value or typed self variants if the implementation supports them cleanly.

## Parameter Pattern Plus Aggregate Long Parameter Step

Date: 2026-06-20

Goal:

- Cover long parameter declarations where the parameter is not always a simple binding.
- Mix pattern forms with aggregate values and aggregate references.
- Stay within supported Rx syntax and avoid exotic invalid Rust-only patterns.

Small probe:

- `/tmp/pattern_aggregate_probe.rx`
  - Covered:
    - `ref p: Pair`
    - `ref arr: [usize; 3]`
    - `&rp: &Pair`
    - `&&rrp: & &Pair`
    - `&ra: &[usize; 3]`
    - `&&rra: & &[usize; 3]`
    - `ref mut v: usize`
    - `&mut mv: &mut usize`
    - wildcard `_: bool`
  - RV64/qemu output: `1`.

Generated long tests:

- `local_tests/long_param_pattern_aggregate_1024.rx`
  - 1024 explicit parameters.
  - 3682 lines.
  - Expected score: `1664`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_pattern_aggregate_2048.rx`
  - 2048 explicit parameters.
  - 7343 lines.
  - Expected score: `3328`.
  - RV64/qemu output: `1`.

Repeating parameter pattern cycle:

- `ref pN: Pair`
- `ref aN: [usize; 3]`
- `&pN: &Pair`
- `&&pN: & &Pair`
- `&aN: &[usize; 3]`
- `&&aN: & &[usize; 3]`
- `_: bool`
- `uN: usize`

Result:

- Both pattern+aggregate long-parameter cases pass.
- This lowers the priority of normal supported destructuring/reference patterns as the hidden `long long param` WA cause.

Next better directions:

- Associated function sret with long parameters, without a method receiver, to isolate hidden return pointer behavior.
- Typed/self by-value method variants if they parse and codegen cleanly.
- Very large but sparse-use parameter lists, closer to OJ hidden tests that may not read every argument.

## Associated Function Sret Long Parameter Step

Date: 2026-06-20

Goal:

- Isolate hidden sret return pointer behavior without a method receiver.
- Use a normal associated function call `Maker::make(...) -> Ret`.
- Keep long mixed user parameters so the hidden return pointer shifts stack/register argument positions.

Generated long tests:

- `local_tests/long_param_assoc_sret_mix_1536.rx`
  - Associated function: `Maker::make(...) -> Ret`.
  - Return type: `Ret { score: usize, data: [usize; 4], ok: bool }`.
  - 1536 explicit parameters.
  - Expected score: `2381`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_assoc_sret_mix_3072.rx`
  - Same shape as the 1536 case.
  - 3072 explicit parameters.
  - Expected score: `4685`.
  - RV64/qemu output: `1`.

Repeating parameter cycle:

- `usize`
- `i32`
- `Pair`
- `[usize; 3]`
- `&Pair`
- `&[usize; 3]`
- `bool`
- `&mut usize`

Result:

- Both associated-function sret long-parameter cases pass.
- This lowers the priority of hidden return pointer shifting alone as the remaining `long long param` WA cause.

Next better directions:

- Typed/self by-value method variants if they parse and codegen cleanly.
- Very large sparse-use parameter lists, closer to hidden tests that may stress parameter save/slot setup without reading every argument.
- Re-check baseline after the recent test-only commits before further code changes.

## Very Large Sparse-Use Long Parameter Step

Date: 2026-06-20

Goal:

- Approximate hidden `looooong looooong param` style where the parameter list is extremely long but the function body may only use selected boundary/tail parameters.
- Avoid full-use 8192+ compile-time blowups while still forcing the compiler to parse, bind, lower, and pass every parameter.
- Keep parameter types normal and mixed.

Baseline note:

- `bash /tmp/qt2.sh RCompiler-Testcases/long-param/src` returned `PASS=34 FAIL=0`.
- `/tmp/qemu_test.sh` was not present in this environment.
- `bash /tmp/qt2.sh RCompiler-Testcases/semantic-2/src` returned `PASS=1 FAIL=49`, so `qt2.sh` is not a valid replacement for the missing semantic-2 oracle/script on this directory layout.

Generated long tests:

- `local_tests/long_param_sparse_use_mix_8192.rx`
  - 8192 explicit parameters.
  - 13354 lines.
  - Checked 264 selected parameters.
  - Expected score: `396`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_sparse_use_mix_16384.rx`
  - 16384 explicit parameters.
  - 26308 lines.
  - Checked 296 selected parameters.
  - Expected score: `444`.
  - RV64/qemu output: `1`.

Repeating parameter cycle:

- `i32`
- `usize`
- `bool`
- `Pair`
- `&Pair`
- `[usize; 3]`
- `&[usize; 3]`
- `&mut usize`

Checked regions:

- beginning of the list
- ABI boundary-adjacent early parameters
- middle ranges around 1000, 4096, and 8192
- dense tail parameters

Result:

- Both sparse-use very-long mixed parameter cases pass.
- This lowers the priority of "parameter list is simply longer than our previous tests" as the remaining WA cause, at least up to 16384 explicit parameters with normal mixed types.

Next better directions:

- Typed/self by-value method variants if they parse and codegen cleanly.
- Long parameter tests where all arguments are function call expressions or returned aggregate values, to stress call argument evaluation order and temporary slots.
- Inspect codegen for function-call argument setup around stack-passed aggregates; hidden WA may depend on temporaries rather than declared parameter types alone.

## Call Argument Temporary Long Parameter Step

Date: 2026-06-20

Goal:

- Test long calls where many arguments are not simple variables/literals but function-call results.
- Stress argument evaluation, temporary aggregate slots, and stack-passed arguments in the caller.
- Keep the callee parameter list normal and mixed.

Generated long tests:

- `local_tests/long_param_call_temporary_mix_1024.rx`
  - 1024 explicit parameters.
  - 3356 lines.
  - Expected score: `1536`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_call_temporary_mix_2048.rx`
  - 2048 explicit parameters.
  - 6684 lines.
  - Expected score: `3072`.
  - RV64/qemu output: `1`.

Argument forms:

- `make_usize(seed) -> usize`
- `make_i32(seed) -> i32`
- `make_bool(seed) -> bool`
- `make_pair(seed, y, ok) -> Pair`
- `make_arr(seed) -> [usize; 3]`
- references to prebuilt `Pair` / `[usize; 3]`
- `&mut usize`

Result:

- Both call-temporary long-parameter cases pass.
- This lowers the priority of ordinary argument temporary preservation and stack-passed aggregate temporaries as the remaining WA cause.

Next better directions:

- Typed/self by-value method variants if they parse and codegen cleanly.
- Nested call expressions as arguments, where stack-passed arguments themselves contain calls that may clobber caller argument setup.
- Inspect actual call lowering for nested calls around stack-passed argument positions if a runtime WA appears.

## Nested Call Argument Long Parameter Step

Date: 2026-06-20

Goal:

- Stress outer call argument setup when many stack-passed arguments are themselves produced by nested function calls.
- Check whether inner calls clobber temporaries or partially prepared stack arguments for the outer long call.
- Keep the test normal: helper functions return scalar/aggregate values used as ordinary arguments.

Generated long tests:

- `local_tests/long_param_nested_call_args_512.rx`
  - 512 explicit parameters.
  - 1693 lines.
  - Expected score: `768`.
  - RV64/qemu output: `1`.
- `local_tests/long_param_nested_call_args_1024.rx`
  - 1024 explicit parameters.
  - 3357 lines.
  - Expected score: `1536`.
  - RV64/qemu output: `1`.

Nested argument forms:

- `make_usize(id(seed))`
- `make_pair(id(seed), make_i32(id(seed)), make_bool(id(seed)))`
- `make_arr(id(seed))`
- `make_bool(id(seed))`
- `make_i32(id(seed))`
- references to prebuilt `Pair` / `[usize; 3]`
- `&mut usize`

Result:

- Both nested-call argument cases pass.
- This lowers the priority of ordinary nested helper calls clobbering long-call argument setup.

Next better directions:

- Typed/self by-value method variants if they parse and codegen cleanly.
- Cases with nested calls specifically in the tail stack-passed argument region and sparse checking at the end of a much larger list.
- Compare assembly around long call argument stores if a future test finally returns a wrong score.

## Typed And By-Value Self Long Parameter Step

Date: 2026-06-20

Goal:

- Cover method receiver forms listed in `AGENTS.md` that were not yet scaled up.
- Keep the long user parameter list normal and mixed.
- Verify receiver boundary effects for both by-value and typed self forms.

Small probe:

- `/tmp/self_variants_probe.rx`
  - Covered:
    - `self`
    - `mut self`
    - `self: Self`
    - `self: &Self`
    - `mut self: &mut Self`
  - RV64/qemu output was `171`, which matches the corrected hand calculation.

Generated long test:

- `local_tests/long_param_self_variants_512.rx`
  - Runs five methods, each with 512 explicit user parameters.
  - Receiver forms:
    - `self`
    - `mut self`
    - `self: Self`
    - `self: &Self`
    - `mut self: &mut Self`
  - Expected total score: `18854`.
  - RV64/qemu output: `1`.

Repeating user parameter cycle:

- `usize`
- `i32`
- `bool`
- `Pair`
- `[usize; 3]`
- `&Pair`
- `&[usize; 3]`
- `&mut usize`

Result:

- Typed/by-value self receiver forms work in long-parameter method calls.
- This lowers the priority of receiver-form boundary movement as the remaining WA cause.

Next better directions:

- Sparse very-large list where only nested-call tail arguments are checked.
- Long parameter lists with many arrays of references, because arrays of references are a more unusual but still spec-aligned aggregate shape.
