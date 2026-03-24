#!/bin/bash
# 运行 REIMU 模拟器
# 使用方法: ./run_reimu.sh [input_asm_file]

# 默认输入文件
ASM_FILE=${1:-test.s}
BUILTIN_FILE="builtin.s"
REIMU_EXEC="./REIMU/build/linux/x86_64/release/reimu"

if [ ! -f "$REIMU_EXEC" ]; then
    echo "Error: REIMU executable not found at $REIMU_EXEC"
    exit 1
fi

if [ ! -f "$ASM_FILE" ]; then
    echo "Error: Input assembly file not found: $ASM_FILE"
    exit 1
fi

if [ ! -f "$BUILTIN_FILE" ]; then
    echo "Error: Builtin assembly file not found: $BUILTIN_FILE"
    exit 1
fi

# 运行 REIMU
# -i 指定输入汇编文件（这里 REIMU 默认读取 test.s 和 builtin.s，但显式指定可能更清晰，不过 REIMU 的 -i 是指定 stdin 输入文件）
# REIMU 默认会加载当前目录下的 test.s 和 builtin.s
# 如果要加载其他文件，可能需要查看 REIMU 的参数文档，或者临时复制为 test.s

# 根据 manual.md，reimu 默认读取 test.s 和 builtin.s
# 如果我们要跑其他文件，比如 hello.s，我们需要把它拷贝成 test.s 或者看看有没有参数指定汇编文件。
# REIMU 的文档没明确说怎么指定汇编文件，只说默认读取 test.s。
# 通常模拟器会有参数指定加载的程序。
# 让我们先假设只能通过覆盖 test.s 来运行。

if [ "$ASM_FILE" != "test.s" ]; then
    cp "$ASM_FILE" test.s
fi

"$REIMU_EXEC" -s=8M
