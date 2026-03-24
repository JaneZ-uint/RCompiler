#!/bin/bash
TEST_DIR="RCompiler-Testcases/semantic-2/src"
COMPILER="./build/RCompiler"
SIMULATOR="./run_reimu.sh"

if [ -z "$1" ]; then
    echo "Usage: $0 <test_name>"
    exit 1
fi

test_name=$1
rx_file="$TEST_DIR/$test_name/$test_name.rx"
in_file="$TEST_DIR/$test_name/$test_name.in"
out_file="$TEST_DIR/$test_name/$test_name.out"

if [ ! -f "$rx_file" ]; then
    echo "Error: Test file $rx_file not found"
    exit 1
fi

cp "$rx_file" tmp.rx
$COMPILER > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

if [ -f "$in_file" ]; then
    cat "$in_file" | $SIMULATOR test.s > output.txt 2>&1
else
    $SIMULATOR test.s > output.txt 2>&1
fi

# Filter output (removing simulator noise)
cat output.txt | sed '1,/^=* Build time:/d' | sed '/^Exiting with status/d' | sed '/^Warning:/d' | sed '/^$/d' > my_output.txt

if [ -f "$out_file" ]; then
    cat "$out_file" | sed '/^$/d' > expected_output.txt
    diff -w -B my_output.txt expected_output.txt
    if [ $? -eq 0 ]; then
        echo "PASS"
    else
        echo "FAIL"
        echo "Expected:"
        cat expected_output.txt
        echo "Got:"
        cat my_output.txt
    fi
else
    echo "No expected output file found. Output:"
    cat my_output.txt
fi
