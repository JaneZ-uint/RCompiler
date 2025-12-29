#! /bin/bash

# 定义颜色输出
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# 获取当前工作目录
CURRENT_DIR=$(pwd)

# 定义路径
COMPILER="$CURRENT_DIR/build/RCompiler"
TEST_DIR="$CURRENT_DIR/RCompiler-Testcases/semantic-2/src"
BUILTIN="$CURRENT_DIR/builtin.ll"

cd "$CURRENT_DIR/build"

# 初始化统计变量
total=0
passed=0

# 检查编译器是否存在
if [ ! -f "$COMPILER" ]; then
    echo "Error: Compiler not found at $COMPILER"
    exit 1
fi

# 检查 builtin.ll 是否存在
if [ ! -f "$BUILTIN" ]; then
    echo "Error: builtin.ll not found at $BUILTIN"
    exit 1
fi

echo "Starting tests..."

# 查找 semantic-2 目录下所有的 .rx 文件
for dir in "$TEST_DIR"/*; do
    if [ ! -d "$dir" ]; then
        continue
    fi

    # 获取文件所在目录和基本文件名（不带后缀）
    basename=$(basename "$dir")
    rx_file="$dir/$basename.rx"
    
    if [ ! -f "$rx_file" ]; then
        continue
    fi

    # 统计总测试用例数
    total=$((total + 1))
    
    # 定义输入和预期输出文件路径
    in_file="$dir/$basename.in"
    out_file="$dir/$basename.out"

    cp "$rx_file" "$CURRENT_DIR/tmp.rx"
    
    # 1. 运行 RCompiler
    # 将 .rx 文件作为参数，并将标准输出重定向到 test.ll
    "$COMPILER"
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Compiler Fail: $basename${NC}"
        continue
    fi

    ir_file="$CURRENT_DIR/test.ll"

    # 2. 使用 Clang 编译 test.ll 和 builtin.ll
    # -Wno-override-module 用于抑制模块覆盖警告
    # -lm 链接数学库（如果需要）
    clang "$BUILTIN" "$ir_file" -o a.out 2>/dev/null
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Clang Fail: $basename${NC}"
        continue
    fi

    # 3. 运行生成的程序 a.out
    # 如果存在对应的 .in 文件，则将其作为输入
    if [ -f "$in_file" ]; then
        ./a.out < "$in_file" > my.out
    else
        ./a.out > my.out
    fi

    # 4. 比较输出结果
    if [ -f "$out_file" ]; then
        # diff -w 忽略空白字符差异，-B 忽略空行
        diff -w -B my.out "$out_file" > /dev/null
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}Correct: $basename${NC}"
            passed=$((passed + 1))
        else
            echo -e "${RED}Error: $basename${NC}"
            # 如果需要查看详细差异，可以取消下面几行的注释
            # echo "Expected:"
            # cat "$out_file"
            # echo "Got:"
            # cat my.out
        fi
    else
        echo -e "${RED}Missing .out file: $basename${NC}"
    fi

    # 清理临时文件
    rm -f test.ll a.out my.out
done

# 输出最终统计结果
echo "----------------TEST RESULT----------------"
echo "Total: $total, Passed: $passed, Failed: $((total - passed))"