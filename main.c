#define GMATH_IMPLEMENTATION
#include "gmath.h"
#include <stdio.h>

int main(void)
{
	float matrix_shape[] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9,
	};

	float matrix_shape2[] = {
		9, 8, 7,
		6, 5, 4,
		3, 2, 1,
	};

	float matrix_shape3[] = {
		3,
		4,
		5,
		1,
	};

	/* Matrix mat[3] = { */
	/* 	{matrix_shape, 3, 3}, */
	/* 	{matrix_shape2, 3, 3}, */
	/* 	GMatrix_malloc(3,3), */
	/* }; */

	Matrix mat[3] = {
		GMatrix_unit(4),
		{matrix_shape3, 1, 4},
		GMatrix_malloc(1, 4),
	};

	GMAT_AT(mat[0], 0, 3) = 1;
	GMAT_AT(mat[0], 1, 3) = 1;
	GMAT_AT(mat[0], 2, 3) = 1;


	GMatrix_print(mat[0]);
	printf("----------------------------------------\n");
	GMatrix_print(mat[1]);

	GMatrix_prod(mat[2], mat[0], mat[1]);
	printf("----------------------------------------\n");
	GMatrix_print(mat[2]);
}
