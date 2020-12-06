#!/bin/bash
# Test the implementation of vector function in vprec backend

bin=binary_compute_vprec_rounding

# Compile test
verificarlo-c -march=native compute_vprec_rounding.c -o $bin

# Delete past result
rm -Rf output_vprec.txt

# Vector variable
vec="1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1"

# Run test
touch output_vprec.txt
export VFC_BACKENDS="libinterflop_vprec.so"
for i in 2 4 8 16
do
    ./$bin float "+" $i $vec >> output_vprec.txt
    ./$bin float "*" $i $vec >> output_vprec.txt
    ./$bin float "-" $i $vec >> output_vprec.txt
    ./$bin float "/" $i $vec >> output_vprec.txt
done

# Test if file is equal
is_equal=$(diff -U 0 result.txt output_vprec.txt | grep ^@ | wc -l)

# Print result
echo $is_equal

# Exit
if [ $is_equal == 0 ] ; then
    exit 0;
else
    exit 1;
fi
