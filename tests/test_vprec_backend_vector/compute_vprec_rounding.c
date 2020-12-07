#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emmintrin.h>
#include <immintrin.h>

// Type definition
typedef double double2 __attribute__((ext_vector_type(2)));
typedef double double4 __attribute__((ext_vector_type(4)));
typedef double double8 __attribute__((ext_vector_type(8)));
typedef double double16 __attribute__((ext_vector_type(16)));
typedef float float2 __attribute__((ext_vector_type(2)));
typedef float float4 __attribute__((ext_vector_type(4)));
typedef float float8 __attribute__((ext_vector_type(8)));
typedef float float16 __attribute__((ext_vector_type(16)));

/* perform_float_vector_bin_op: applies the binary operator (op) to vectors (a) and (b) */
/* and stores the result in vector (res) */
void perform_float_vector_binary_op(unsigned long long size, char op,
				    void *res, void *a, void *b) {
  switch (size) {
  case 2:
    fprintf(stderr, "invalid vector of size %llu for type float\n", size);
    exit(EXIT_FAILURE);
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
      fprintf(stderr, "invalid operator %c for vector of size %llu for type float\n", op, size);
      exit(EXIT_FAILURE);
      break;
    };
    break;
#else
    fprintf(stderr, "sse instruction not available\n");
    exit(EXIT_FAILURE);
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
      fprintf(stderr, "invalid operator %c for vector of size %llu for type float\n", op, size);
      exit(EXIT_FAILURE);
      break;
    };
    break;
#else
    fprintf(stderr, "avx instruction not available\n");
    exit(EXIT_FAILURE);
    break;
#endif
  case 16:
#ifdef __AVX512F__
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
      fprintf(stderr, "invalid operator %c for vector of size %llu for type float\n", op, size);
      exit(EXIT_FAILURE);
      break;
    };
    break;
#else
    fprintf(stderr, "avx512 instruction not available\n");
    exit(EXIT_FAILURE);
    break;
#endif
  default:
    fprintf(stderr, "invalid size %llu\n", size);
    exit(EXIT_FAILURE);
    break;
  };
}

/* perform_double_vector_bin_op: applies the binary operator (op) to vectors (a) and (b) */
/* and stores the result in vector (res) */
void perform_double_vector_binary_op(unsigned long long size, char op,
				    void *res, void *a, void *b) {
  switch (size) {
  case 2:
#ifdef __SSE__
    switch (op) {
    case '+':
      *(double2 *)res = (double2)_mm_add_pd(*(double2 *)a, *(double2 *)b);
      break;
    case '*':
      *(double2 *)res = (double2)_mm_mul_pd(*(double2 *)a, *(double2 *)b);
      break;
    case '-':
      *(double2 *)res = (double2)_mm_sub_pd(*(double2 *)a, *(double2 *)b);
      break;
    case '/':
      *(double2 *)res = (double2)_mm_div_pd(*(double2 *)a, *(double2 *)b);
      break;
    default:
      fprintf(stderr, "invalid operator %c for vector of size %llu for type float\n", op, size);
      exit(EXIT_FAILURE);
      break;
    };
    break;
#else
    fprintf(stderr, "sse instruction not available\n");
    exit(EXIT_FAILURE);
    break;
#endif
  case 4:
#ifdef __AVX__
    switch (op) {
    case '+':
      *(double4 *)res = (double4)_mm256_add_pd(*(double4 *)a, *(double4 *)b);
      break;
    case '*':
      *(double4 *)res = (double4)_mm256_mul_pd(*(double4 *)a, *(double4 *)b);
      break;
    case '-':
      *(double4 *)res = (double4)_mm256_sub_pd(*(double4 *)a, *(double4 *)b);
      break;
    case '/':
      *(double4 *)res = (double4)_mm256_div_pd(*(double4 *)a, *(double4 *)b);
      break;
    default:
      fprintf(stderr, "invalid operator %c for vector of size %llu for type float\n", op, size);
      exit(EXIT_FAILURE);
      break;
    };
    break;
#else
    fprintf(stderr, "avx instruction not available\n");
    exit(EXIT_FAILURE);
    break;
#endif
  case 8:
#ifdef __AVX512F__
    switch (op) {
    case '+':
      *(double8 *)res = (double8)_mm512_add_pd(*(double8 *)a, *(double8 *)b);
      break;
    case '*':
      *(double8 *)res = (double8)_mm512_mul_pd(*(double8 *)a, *(double8 *)b);
      break;
    case '-':
      *(double8 *)res = (double8)_mm512_sub_pd(*(double8 *)a, *(double8 *)b);
      break;
    case '/':
      *(double8 *)res = (double8)_mm512_div_pd(*(double8 *)a, *(double8 *)b);
      break;
    default:
      fprintf(stderr, "invalid operator %c for vector of size %llu for type float\n", op, size);
      exit(EXIT_FAILURE);
      break;
    };
    break;
#else
    fprintf(stderr, "avx512 instruction not available\n");
    exit(EXIT_FAILURE);
    break;
#endif
  case 16:
    fprintf(stderr, "invalid vector of size %llu for type double\n", size);
    exit(EXIT_FAILURE);
    break;
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
    switch (size) {
    case 2:
      {
	float2 a_2x;
	float2 b_2x;
	float2 res_2x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_2x[i] = strtof(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_2x[i] = strtof(argv[4 + size + i], NULL);
	}

	perform_float_vector_binary_op(size, op, &res_2x, &a_2x, &b_2x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_2x[i]);
	}
	break;
      }
    case 4:
      {
	float4 a_4x;
	float4 b_4x;
	float4 res_4x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_4x[i] = strtof(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_4x[i] = strtof(argv[4 + size + i], NULL);
	}

	perform_float_vector_binary_op(size, op, &res_4x, &a_4x, &b_4x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_4x[i]);
	}
	break;
      }
    case 8:
      {
	float8 a_8x;
	float8 b_8x;
	float8 res_8x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_8x[i] = strtof(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_8x[i] = strtof(argv[4 + size + i], NULL);
	}

	perform_float_vector_binary_op(size, op, &res_8x, &a_8x, &b_8x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_8x[i]);
	}
	break;
      }
    case 16:
      {
	float16 a_16x;
	float16 b_16x;
	float16 res_16x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_16x[i] = strtof(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_16x[i] = strtof(argv[4 + size + i], NULL);
	}

	perform_float_vector_binary_op(size, op, &res_16x, &a_16x, &b_16x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_16x[i]);
	}
	break;
      }
    };
  }
  else if (strcmp(precision, "double") == 0) {
    switch (size) {
    case 2:
      {
	double2 a_double_2x;
	double2 b_double_2x;
	double2 res_double_2x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_double_2x[i] = strtod(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_double_2x[i] = strtod(argv[4 + size + i], NULL);
	}

	perform_double_vector_binary_op(size, op, &res_double_2x, &a_double_2x, &b_double_2x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_double_2x[i]);
	}
	break;
      }
    case 4:
      {
	double4 a_double_4x;
	double4 b_double_4x;
	double4 res_double_4x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_double_4x[i] = strtod(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_double_4x[i] = strtod(argv[4 + size + i], NULL);
	}

	perform_double_vector_binary_op(size, op, &res_double_4x, &a_double_4x, &b_double_4x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_double_4x[i]);
	}
	break;
      }
    case 8:
      {
	double8 a_double_8x;
	double8 b_double_8x;
	double8 res_double_8x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_double_8x[i] = strtod(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_double_8x[i] = strtod(argv[4 + size + i], NULL);
	}

	perform_double_vector_binary_op(size, op, &res_double_8x, &a_double_8x, &b_double_8x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_double_8x[i]);
	}
	break;
      }
    case 16:
      {
	double16 a_double_16x;
	double16 b_double_16x;
	double16 res_double_16x;
	printf("%s %c %lld\n", precision, op, size);

	for (unsigned long long i = 0; i < size; ++i) {
	  a_double_16x[i] = strtod(argv[4 + i], NULL);
	}

	for (unsigned long long i = 0; i < size; ++i) {
	  b_double_16x[i] = strtod(argv[4 + size + i], NULL);
	}

	perform_double_vector_binary_op(size, op, &res_double_16x, &a_double_16x, &b_double_16x);

	for (unsigned long long i = 0; i < size; ++i) {
	  printf("%f\n", res_double_16x[i]);
	}
	break;
      }
    };
  }
  else {
    fprintf(stderr, "Bad type : float | double\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
