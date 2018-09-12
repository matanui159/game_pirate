#include "matrix.h"

void matrix_identity(matrix_t* matrix) {
	*matrix = (matrix_t) {
		.m00 = 1,
		.m11 = 1,
		.m22 = 1,
		.m33 = 1
	};
}