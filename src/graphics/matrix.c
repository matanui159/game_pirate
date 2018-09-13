#include "matrix.h"
#include <math.h>

static inline __m128 linear_comb(__m128* left, matrix_t* right) {
	__m128 shuffle = _mm_shuffle_ps(*left, *left, 0x00);
	__m128 result = _mm_mul_ps(shuffle, right->row0);

	shuffle = _mm_shuffle_ps(*left, *left, 0x55);
	result = _mm_add_ps(result, _mm_mul_ps(shuffle, right->row1));

	shuffle = _mm_shuffle_ps(*left, *left, 0xAA);
	result = _mm_add_ps(result, _mm_mul_ps(shuffle, right->row2));

	shuffle = _mm_shuffle_ps(*left, *left, 0xFF);
	return _mm_add_ps(result, _mm_mul_ps(shuffle, right->row3));
}

static inline void cos_sin(float angle, float* c, float* s) {
	angle = angle * 0.01745329;
	*c = cos(angle);
	*s = sin(angle);
}

matrix_t matrix_identity() {
	return (matrix_t) {
		.m00 = 1,
		.m11 = 1,
		.m22 = 1,
		.m33 = 1
	};
}

matrix_t matrix_multiply(matrix_t* left, matrix_t* right) {
	return (matrix_t) {
		.row0 = linear_comb(&left->row0, right),
		.row1 = linear_comb(&left->row1, right),
		.row2 = linear_comb(&left->row2, right),
		.row3 = linear_comb(&left->row3, right)
	};
}

matrix_t matrix_translate(matrix_t* matrix, float x, float y, float z) {
	matrix_t translate = (matrix_t) {
		.m00 = 1, .m03 = x,
		.m11 = 1, .m13 = y,
		.m22 = 1, .m23 = z,
		.m33 = 1
	};
	return matrix_multiply(matrix, &translate);
}

matrix_t matrix_scale(matrix_t* matrix, float x, float y, float z) {
	matrix_t scale = (matrix_t) {
		.m00 = x,
		.m11 = y,
		.m22 = z,
		.m33 = 1
	};
	return matrix_multiply(matrix, &scale);
}

matrix_t matrix_rotx(matrix_t* matrix, float angle) {
	float c, s;
	cos_sin(angle, &c, &s);
	matrix_t rotx = (matrix_t) {
		.m00 = 1,
		.m11 = c, .m12 = -s,
		.m21 = s, .m22 = c,
		.m33 = 1
	};
	return matrix_multiply(matrix, &rotx);
}

matrix_t matrix_roty(matrix_t* matrix, float angle) {
	float c, s;
	cos_sin(angle, &c, &s);
	matrix_t roty = (matrix_t) {
		.m00 = c, .m02 = s,
		.m11 = 1,
		.m20 = -s, .m22 = c,
		.m33 = 1
	};
	return matrix_multiply(matrix, &roty);
}

matrix_t matrix_rotz(matrix_t* matrix, float angle) {
	float c, s;
	cos_sin(angle, &c, &s);
	matrix_t rotz = (matrix_t) {
		.m00 = c, .m01 = -s,
		.m10 = s, .m11 = c,
		.m22 = 1,
		.m33 = 1
	};
	return matrix_multiply(matrix, &rotz);
}