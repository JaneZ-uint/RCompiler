#!/bin/bash

TEST_DIR="RCompiler-Testcases/semantic-2/src"
COMPILER="./build/RCompiler"
SIMULATOR="./run_reimu.sh"
TOTAL=0
PASSED=0

echo "Starting codegen tests..."

# Ensure we have the builtin.s available (run_reimu.sh needs it)
if [ ! -f "builtin.s" ]; then
    echo "Error: builtin.s not found!"
    exit 1
fi

for test_path in "$TEST_DIR"/comprehensive*; do
    if [ ! -d "$test_path" ]; then continue; fi

    base_name=$(basename "$test_path")
    rx_file="$test_path/$base_name.rx"
    in_file="$test_path/$base_name.in"
    out_file="$test_path/$base_name.out"

    # Step 1: Copy rx file
    cp "$rx_file" tmp.rx

    # Step 2: Compile
    $COMPILER > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "FAIL: $base_name (Compilation failed)"
        TOTAL=$((TOTAL + 1))
        continue
    fi
    
    # Step 3: Run simulator
    if [ -f "$in_file" ]; then
        INPUT_CMD="cat $in_file"
    else
        INPUT_CMD="cat /dev/null"
    fi

    # Capture output
    OUTPUT=$($INPUT_CMD | $SIMULATOR test.s 2>&1)
    
    # Filter output
    # Remove header (up to Build time line), footer (Exiting with status), warnings
    echo "$OUTPUT" | \
    sed '1,/^=* Build time:/d' | \
    sed '/^Exiting with status/d' | \
    sed '/^Warning:/d' | \
    sed '/^$/d' > my_output.txt
    
    # Prepare expected output (remove empty lines for consistency with our filtered output)
    if [ -f "$out_file" ]; then
        cat "$out_file" | sed '/^$/d' > expected_output.txt
    else
        touch expected_output.txt
    fi

    # Compare
    # -w ignores white space, -B ignores blank lines
    diff -w -B my_output.txt expected_output.txt > /dev/null
    if [ $? -eq 0 ]; then
        echo "PASS: $base_name"
        PASSED=$((PASSED + 1))
    else
        echo "FAIL: $base_name"
        echo "  Expected:"
        cat expected_output.txt | sed 's/^/    /'
        echo "  Got:"
        cat my_output.txt | sed 's/^/    /'
        # echo "  Raw Output excerpt:"
        # echo "$OUTPUT" | head -n 20 | sed 's/^/    /'
    fi
    TOTAL=$((TOTAL + 1))
    
    # Clean up
    rm -f my_output.txt expected_output.txt
done

echo "----------------------------------------"
echo "Tests passed: $PASSED / $TOTAL"
