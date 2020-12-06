#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>
#include <emmintrin.h>

// Type definition
typedef double double2 __attribute__((ext_vector_type(2)));
typedef double double4 __attribute__((ext_vector_type(4)));
typedef double double8 __attribute__((ext_vector_type(8)));
typedef double double16 __attribute__((ext_vector_type(16)));
typedef float float2 __attribute__((ext_vector_type(2)));
typedef float float4 __attribute__((ext_vector_type(4)));
typedef float float8 __attribute__((ext_vector_type(8)));
typedef float float16 __attribute__((ext_vector_type(16)));

/* perform vector operation in scalar mode */
void perform_float_scalar_vector_binary_op(unsigned long long size, char op,
				     float *res, float *a, float *b) {
  switch (op) {							
  case '+':						
    for (int i = 0; i < size; ++i) {				
      res[i] = a[i] + b[i];					
    }								
    break;							
  case '*':						
    for (int i = 0; i < size; ++i) {				
      res[i] = a[i] * b[i];					
    }								
    break;							
  case '-':						
    for (int i = 0; i < size; ++i) {				
      res[i] = a[i] - b[i];					
    }								
    break;							
  case '/':						
    for (int i = 0; i < size; ++i) {				
      res[i] = a[i] / b[i];					
    }								
    break;							
  default:							
    fprintf(stderr, "invalid operator %c", op);			
    exit(EXIT_FAILURE);						
    break;							
  };
}

/* perform_float_vector_bin_op: applies the binary operator (op) to vectors (a) and (b) */
/* and stores the result in vector (res) */
void perform_float_vector_binary_op(unsigned long long size, char op,
				    void *res, void *a, void *b) {
  switch (size) {						
  case 2:							
    perform_float_scalar_vector_binary_op(size, op, res, a, b);	
    break;							
  case 4:							
#ifdef __SSE__						
    switch (op) {						
    case '+':						
      *(float4 *)res = (float4)_mm_add_ps(*(float4 *)a, *(float4 *)b);
      break;
    case '*':						
      *(float4 *)res = (float4)_mm_mul_ps(*(float4 *)a, *(float4 *)b);
      break;
    case '-':						
      *(float4 *)res = (float4)_mm_sub_ps(*(float4 *)a, *(float4 *)b);
      break;
    case '/':						
      *(float4 *)res = (float4)_mm_div_ps(*(float4 *)a, *(float4 *)b);				
      break;
    default:							
      fprintf(stderr, "invalid operator %c for size %llu\n", op, size);		
      exit(EXIT_FAILURE);					
      break;							
    };							
#else							
    perform_float_scalar_vector_binary_op(size, op, res, a, b);	
    break;							
#endif							
  case 8:							
#ifdef __AVX__						
    switch (op) {						
    case '+':						
      *(float8 *)res = (float8)_mm256_add_ps(*(float8 *)a, *(float8 *)b);
      break;
    case '*':						
      *(float8 *)res = (float8)_mm256_mul_ps(*(float8 *)a, *(float8 *)b);				
      break;
    case '-':						
      *(float8 *)res = (float8)_mm256_sub_ps(*(float8 *)a, *(float8 *)b);				
      break;
    case '/':						
      *(float8 *)res = (float8)_mm256_div_ps(*(float8 *)a, *(float8 *)b);				
      break;
    default:							
      fprintf(stderr, "invalid operator %c for size %llu\n", op, size);
      exit(EXIT_FAILURE);					
      break;							
    };							
#else							
    perform_float_scalar_vector_binary_op(size, op, res, a, b);	
    break;							
#endif							
  case 16:							
#ifdef __AVX512__						
    switch (op) {						
    case '+':						
      *(float16 *)res = (float16)_mm512_add_ps(*(float16 *)a, *(float16 *)b);				
      break;
    case '*':						
      *(float16 *)res = (float16)_mm512_mul_ps(*(float16 *)a, *(float16 *)b);				
      break;
    case '-':						
      *(float16 *)res = (float16)_mm512_sub_ps(*(float16 *)a, *(float16 *)b);				
      break;
    case '/':						
      *(float16 *)res = (float16)_mm512_div_ps(*(float16 *)a, *(float16 *)b);				
      break;
    default:							
      fprintf(stderr, "invalid operator %c for size %llu\n", op, size);		
      exit(EXIT_FAILURE);					
      break;							
    };							
#else							
    perform_float_scalar_vector_binary_op(size, op, res, a, b);	
    break;							
#endif							
  default:							
    fprintf(stderr, "invalid size %llu\n", size);			
    exit(EXIT_FAILURE);						
    break;							
  };
}


int main(int argc, char **argv) {

  if (argc < 3) {
    fprintf(stderr, "at least 3 arguments expected: type op size [list of member a] [list of member b]\n");
    exit(EXIT_FAILURE);
  }

  char *precision = argv[1];
  char op = argv[2][0];
  unsigned long long size = strtoll(argv[3], NULL, 10);

  if (strcmp(precision, "float") == 0) {
    printf("%s %c %lld\n", precision, op, size);
    
    float a[size];
    float b[size];
    float res[size];
    
    for (unsigned long long i = 0; i < size; ++i) {
      a[i] = strtof(argv[4 + i], NULL);
    }

    for (unsigned long long i = 0; i < size; ++i) {
      b[i] = strtof(argv[4 + size + i], NULL);
    }

    perform_float_vector_binary_op(size, op, &res, &a, &b);
    for (unsigned long long i = 0; i < size; ++i) {
      printf("%f\n", res[i]);
    }
  }
  else if (strcmp(precision, "double") == 0) {
    fprintf(stderr, "Not yet supported\n");
    exit(EXIT_FAILURE);
  }
  else {
    fprintf(stderr, "Bad type : float | double\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
