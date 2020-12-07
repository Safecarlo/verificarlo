#!/bin/bash
# Test the implementation of vector function in vprec backend

bin=binary_compute_vprec_rounding

# Delete past result
rm -Rf output*.txt

# Variable
cpuinfo=$(cat /proc/cpuinfo)

is_sse=$(echo $cpuinfo | grep sse | wc -l)
is_avx=$(echo $cpuinfo | grep avx | wc -l)
is_avx512=$(echo $cpuinfo | grep avx512 | wc -l)

if [ $is_sse == 1 ] || [ $is_avx == 1 ] || [ $is_avx512 == 1 ] ; then
    is_none=0
else
    is_none=1
fi

vec="1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1 1.1"

# Compile and run the program
# Take the architecture flags on parameter and the output file
compile_and_run()
{
    export VFC_BACKENDS_SILENT_LOAD="True"
    export VFC_BACKENDS_LOGGER="False"
    
    # Compile test
    verificarlo-c $1 compute_vprec_rounding.c -o $bin

    # Run test
    touch output_vprec.txt
    export VFC_BACKENDS="libinterflop_vprec.so"
    for i in 2 4 8 16
    do
	for type in float double
	do
	    ./$bin $type "+" $i $vec >> $2
	    ./$bin $type "*" $i $vec >> $2
	    ./$bin $type "-" $i $vec >> $2
	    ./$bin $type "/" $i $vec >> $2
	done
    done

    unset VFC_BACKENDS_SILENT_LOAD
    export VFC_BACKENDS_LOGGER="True"
}

# Test if file is equal
is_equal=1
if [ $is_none == 1 ] ; then
    compile_and_run "" output_none.txt
    is_equal=$(diff -U 0 result_none.txt output_none.txt | grep ^@ | wc -l)
elif [ true ] ; then
    # SSE
    if [ $is_sse == 1 ]; then
	compile_and_run -msse output_sse.txt
	is_equal=$(diff -U 0 result_sse.txt output_sse.txt | grep ^@ | wc -l)
    fi

    # AVX
    if [ $is_avx == 1 ] ; then
	compile_and_run -mavx output_avx.txt
	is_equal=$(diff -U 0 result_avx.txt output_avx.txt | grep ^@ | wc -l)
    fi

    # AVX512F
    if [ $is_avx512 == 1 ] ; then
	compile_and_run -mavx512f output_avx512.txt
	is_equal=$(diff -U 0 result_avx512.txt output_avx512.txt | grep ^@ | wc -l)
    fi
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
