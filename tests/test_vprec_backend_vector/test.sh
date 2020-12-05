#!/bin/bash
# Test the implementation of vector function in vprec backend

bin=binary_compute_vprec_rounding

# Compile test
verificarlo-c compute_vprec_rounding.c -o $bin

# Delete past result
rm -Rf output*

# Run test
export VFC_BACKENDS="libinterflop_ieee.so"
./$bin float + 2 0.01 0.7 5565.0 666.000099 > output_iee.txt
export VFC_BACKENDS="libinterflop_vprec.so"
./$bin float + 2 0.01 0.7 5565.0 666.000099 > output_vprec.txt

# Test if file is equal
is_equal_iee=$(diff -U 0 result.txt output_iee.txt | grep ^@ | wc -l)
is_equal_vprec=$(diff -U 0 result.txt output_vprec.txt | grep ^@ | wc -l)

# Group result
test_pass=$(((! $is_equal_iee) && $is_equal_vprec))

# Print result
echo $test_pass

# Exit
if [ $test_pass == 0 ] ; then
    exit 0;
else
    exit 1;
fi
