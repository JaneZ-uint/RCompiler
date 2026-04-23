#!/bin/bash
# RCompiler 评测脚本
# 用法: ./test.sh [选项]
#   ./test.sh              运行全部 50 个测试点
#   ./test.sh 23           运行单个测试点
#   ./test.sh 10 20        运行测试点 10 到 20
#   ./test.sh -v           详细模式（显示每个测试点的输出对比）

set -euo pipefail

# ======================== 配置 ========================
ROOT="$(cd "$(dirname "$0")" && pwd)"
BUILD="$ROOT/build"
REIMU="$ROOT/REIMU/build/linux/x86_64/release/reimu"
TESTDIR="$ROOT/RCompiler-Testcases/semantic-2/src"
BUILTIN="$ROOT/builtin.s"
TIMEOUT=120
REIMU_MEM="16M"

# 颜色
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

# ======================== 参数解析 ========================
VERBOSE=0
START=1
END=50

while [[ $# -gt 0 ]]; do
    case "$1" in
        -v|--verbose) VERBOSE=1; shift ;;
        -h|--help)
            echo "用法: $0 [选项] [起始] [结束]"
            echo "  -v, --verbose   详细模式，显示 diff"
            echo "  -h, --help      显示帮助"
            echo "示例:"
            echo "  $0              运行全部 50 个测试点"
            echo "  $0 23           只运行测试点 23"
            echo "  $0 10 20        运行测试点 10 到 20"
            echo "  $0 -v 23        详细模式运行测试点 23"
            exit 0
            ;;
        *)
            if [[ -z "${2:-}" || "$2" == -* ]]; then
                START="$1"; END="$1"
            else
                START="$1"; END="$2"; shift
            fi
            shift
            ;;
    esac
done

# ======================== 检查环境 ========================
if [[ ! -x "$REIMU" ]]; then
    echo -e "${RED}错误: REIMU 模拟器不存在: $REIMU${NC}"
    exit 1
fi

if [[ ! -f "$BUILD/RCompiler" ]]; then
    echo -e "${YELLOW}编译器未构建，正在构建...${NC}"
    cd "$BUILD" && cmake --build . -j 2>&1 | tail -3
fi

# ======================== 辅助函数 ========================
normalize() {
    # 去除 \r，去除每行尾部空白，删除空行
    sed 's/\r$//' | sed 's/[[:space:]]*$//' | sed '/^[[:space:]]*$/d'
}

# ======================== 运行测试 ========================
PASS=0
FAIL=0
FAIL_LIST=""
TOTAL=0

echo -e "${BOLD}══════════════════════════════════════════════════${NC}"
echo -e "${BOLD}  RCompiler 评测  (comprehensive${START}-${END})${NC}"
echo -e "${BOLD}══════════════════════════════════════════════════${NC}"
echo ""

for i in $(seq "$START" "$END"); do
    TOTAL=$((TOTAL + 1))
    DIR="$TESTDIR/comprehensive${i}"
    RX="$DIR/comprehensive${i}.rx"
    IN="$DIR/comprehensive${i}.in"
    EXPECTED="$DIR/comprehensive${i}.out"

    if [[ ! -f "$RX" ]]; then
        echo -e "  ${YELLOW}[SKIP]${NC} comprehensive${i} — 源文件不存在"
        TOTAL=$((TOTAL - 1))
        continue
    fi

    # 编译
    cp "$RX" "$ROOT/tmp.rx"
    cd "$BUILD"
    if ! ./RCompiler 2>/dev/null; then
        echo -e "  ${RED}[CE]${NC}   comprehensive${i} — 编译失败"
        FAIL=$((FAIL + 1))
        FAIL_LIST="$FAIL_LIST $i"
        cd "$ROOT"
        continue
    fi
    cd "$ROOT"

    # 运行
    IN_ARG="$IN"
    [[ ! -f "$IN" ]] && IN_ARG="/dev/null"

    if ! timeout "$TIMEOUT" "$REIMU" -s="$REIMU_MEM" \
        -i="$IN_ARG" -o=test.out \
        -f=test.s,"$BUILTIN" 2>/dev/null; then
        echo -e "  ${RED}[TLE]${NC}  comprehensive${i} — 运行超时或异常"
        FAIL=$((FAIL + 1))
        FAIL_LIST="$FAIL_LIST $i"
        continue
    fi

    # 对比输出
    ACTUAL=$(normalize < test.out)
    EXPECT=$(normalize < "$EXPECTED")

    if [[ "$ACTUAL" == "$EXPECT" ]]; then
        echo -e "  ${GREEN}[AC]${NC}   comprehensive${i}"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}[WA]${NC}   comprehensive${i}"
        FAIL=$((FAIL + 1))
        FAIL_LIST="$FAIL_LIST $i"

        if [[ $VERBOSE -eq 1 ]]; then
            echo -e "    ${CYAN}--- diff (actual vs expected) ---${NC}"
            diff <(echo "$ACTUAL") <(echo "$EXPECT") | head -20 | sed 's/^/    /'
            echo ""
        fi
    fi
done

# ======================== 汇总 ========================
echo ""
echo -e "${BOLD}══════════════════════════════════════════════════${NC}"
if [[ $FAIL -eq 0 ]]; then
    echo -e "  ${GREEN}${BOLD}全部通过！${NC} ${PASS}/${TOTAL}"
else
    echo -e "  ${RED}${BOLD}通过: ${PASS}/${TOTAL}  失败: ${FAIL}${NC}"
    echo -e "  失败测试点:${FAIL_LIST}"
fi
echo -e "${BOLD}══════════════════════════════════════════════════${NC}"

exit $FAIL
