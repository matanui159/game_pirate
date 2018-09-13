#ifndef MATRIX_H_
#define MATRIX_H_
#include <xmmintrin.h>

typedef struct matrix_t {
	union {
		struct {
			__m128 row0;
			__m128 row1;
			__m128 row2;
			__m128 row3;
		};
		struct {
			float m00;
			float m01;
			float m02;
			float m03;
			float m10;
			float m11;
			float m12;
			float m13;
			float m20;
			float m21;
			float m22;
			float m23;
			float m30;
			float m31;
			float m32;
			float m33;
		};
	};
} matrix_t;

matrix_t matrix_identity();

matrix_t matrix_multiply(matrix_t* left, matrix_t* right);
matrix_t matrix_translate(matrix_t* matrix, float x, float y, float z);
matrix_t matrix_scale(matrix_t* matrix, float x, float y, float z);
matrix_t matrix_rotx(matrix_t* matrix, float angle);
matrix_t matrix_roty(matrix_t* matrix, float angle);
matrix_t matrix_rotz(matrix_t* matrix, float angle);
matrix_t matrix_perspective(matrix_t* matrix, float near, float far,
	float angle, float ratio);

#endif