#!/bin/bash

# Configuration
COMPILER_DIR="build"
COMPILER="./RCompiler"
REIMU="./REIMU/build/linux/x86_64/release/reimu"
TEST_ROOT="RCompiler-Testcases/semantic-2/src"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

total=0
pass=0

# Check dependencies
if [ ! -f "$COMPILER_DIR/$COMPILER" ]; then
    echo "Error: Compiler not found at $COMPILER_DIR/$COMPILER"
    exit 1
fi

if [ ! -f "$REIMU" ]; then
    echo "Error: Reimu not found at $REIMU"
    exit 1
fi

if [ ! -f "builtin.s" ]; then
    echo "Error: builtin.s not found in current directory"
    exit 1
fi

for i in {1..50}; do
    test_dir="$TEST_ROOT/comprehensive$i"
    rx_file="$test_dir/comprehensive$i.rx"
    in_file="$test_dir/comprehensive$i.in"
    out_file="$test_dir/comprehensive$i.out"
    
    # Skip if test case doesn't exist
    if [ ! -f "$rx_file" ]; then
        continue
    fi
    
    ((total++))
    
    # 1. Prepare Source
    cp "$rx_file" tmp.rx
    
    # 2. Compile (Generate Executable/ASM)
    rm -f test.s
    cd "$COMPILER_DIR" || exit 1
    $COMPILER > /dev/null 2>&1
    compile_ret=$?
    cd ..
    
    if [ $compile_ret -ne 0 ]; then
        # Failed to generate executable
        # Print error reason in black (default color)
        if [ -f "test.s" ]; then
            cat test.s
        else
            echo "Compilation failed (no output)"
        fi
        continue
    fi
    
    # 3. Prepare Input
    if [ -f "$in_file" ]; then
        cp "$in_file" test.in
    else
        touch test.in
    fi
    
    # 4. Execute (Run Reimu)
    rm -f test.out
    # Command: reimu -i=test.in -o test.out
    # We strip output to adhere to "no other output" rule
    $REIMU -i=test.in -o test.out > /dev/null 2>&1
    
    # 5. Compare Results
    if [ -f "$out_file" ]; then
        if [ ! -f "test.out" ]; then
             echo -e "${RED}Result inconsistent${NC}"
             continue
        fi
        
        diff -w -B test.out "$out_file" > /dev/null
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}Success${NC}"
            ((pass++))
        else
            echo -e "${RED}Result inconsistent${NC}"
        fi
    else
        # If no expected output, handled as per requirement?
        # User implies comparison with comprehensivei.out is always possible.
        # If missing, we can't verify, but printing nothing might be best or specific error.
        echo "Missing .out file"
    fi
    
done

echo "$pass/$total"
