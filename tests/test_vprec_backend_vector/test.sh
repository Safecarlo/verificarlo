#!/bin/bash
# Test the implementation of vector function in vprec backend

bin=binary_compute_vprec_rounding

# Compile test
verificarlo-c -march=native compute_vprec_rounding.c -o $bin

# Delete past result
rm -Rf output_vprec.txt

# Variable
cpuinfo=$(cat /proc/cpuinfo)
is_sse=$(echo $cpuinfo | grep sse | grep ^@ | wc -l)
is_avx=$(echo $cpuinfo | grep avx | grep ^@ | wc -l)
is_avx512=$(echo $cpuinfo | grep avx512 | grep ^@ | wc -l)
is_none=$(! ($is_sse && $is_avx && $is_avx512) )
vec="1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1"

# Run test
touch output_vprec.txt
export VFC_BACKENDS="libinterflop_vprec.so"
for i in 2 4 8 16
do
    for type in float double
    do
	./$bin $type "+" $i $vec >> output_vprec.txt
	./$bin $type "*" $i $vec >> output_vprec.txt
	./$bin $type "-" $i $vec >> output_vprec.txt
	./$bin $type "/" $i $vec >> output_vprec.txt
    done
done

# Test if file is equal
if [ $is_none ] ; then
    is_equal=$(diff -U 0 result_none.txt output_vprec.txt | grep ^@ | wc -l)
elif [ $is_sse ] ; then
    is_equal=$(diff -U 0 result_sse.txt output_vprec.txt | grep ^@ | wc -l)
elif [ $is_sse && $is_avx ] ; then
    is_equal=$(diff -U 0 result_avx.txt output_vprec.txt | grep ^@ | wc -l)
elif [ $is_sse && $is_avx && $is_avx512 ] ; then
    is_equal=$(diff -U 0 result_avx512.txt output_vprec.txt | grep ^@ | wc -l)
else
    echo "Erreur: no arch selected"
    exit 1;
fi	 

# Print result
echo $is_equal

# Clean folder
rm -Rf *~ *.o $bin

# Exit
if [ $is_equal == 0 ] ; then
    exit 0;
else
    exit 1;
fi
