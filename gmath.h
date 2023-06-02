#ifndef GMATH_H
#define GMATH_H

#define GMAT_AT(m, r, c)	((m).mat[(r) * (m).width + (c)])

#include <stdio.h>

typedef struct {
	float *mat;
	short width;
	short height;
} Matrix;

Matrix GMatrix_malloc(short width, short height);
void GMatrix_fill(Matrix mat, float var);

Matrix GMatrix_unit(short size);
void GMatrix_print(const Matrix mat);


/**
 * Return 0 on success
 */
void GMatrix_sum(Matrix dest, const Matrix mat);
void GMatrix_sub(Matrix dest, const Matrix mat);
void GMatrix_scal(Matrix dest, int val);
void GMatrix_prod(Matrix dest, const Matrix mat1, const Matrix mat2);

#endif

#ifdef GMATH_IMPLEMENTATION

#ifndef GMATH_MALLOC
#include <stdlib.h>
#define GMATH_MALLOC malloc
#endif

#ifndef GMATH_ASSERT
#include <assert.h>
#define GMATH_ASSERT(n) assert((n))
#endif

Matrix GMatrix_malloc(short width, short height){
	float* mat = GMATH_MALLOC(sizeof(float)*width*height);
	Matrix ret = {.mat=mat, .width=width, .height=height};
	return ret;
}
void GMatrix_fill(Matrix mat, float var){
	for(int i = 0; i < mat.width * mat.height; i++){
		mat.mat[i] = var;
	}
}

Matrix GMatrix_unit(short size){
	Matrix ret = GMatrix_malloc(size, size);
	GMatrix_fill(ret, 0);
	for (int i = 0; i < size; ++i) {
		GMAT_AT(ret, i, i) = 1;
	}
	return ret;
}

void GMatrix_print(const Matrix mat){
	for (int i = 0; i < mat.height; ++i) {
		for (int j = 0; j < mat.width; ++j) {
			printf("%f\t",GMAT_AT(mat, i, j));
		}
		printf("\n");
	}
}

/**
 * Return 0 on su
 */
void GMatrix_sum(Matrix dest, const Matrix mat){
	GMATH_ASSERT(dest.width == mat.width);
	GMATH_ASSERT(dest.height == mat.height);
	for(int row = 0; row < dest.height; row++){
		for(int column = 0; column < dest.width; column++){
			GMAT_AT(dest, row, column) += GMAT_AT(mat, row, column);
		}
	}
}
void GMatrix_sub(Matrix dest, const Matrix mat){
	GMATH_ASSERT(dest.width == mat.width);
	GMATH_ASSERT(dest.height == mat.height);
	for(int row = 0; row < dest.height; row++){
		for(int column = 0; column < dest.width; column++){
			GMAT_AT(dest, row, column) -= GMAT_AT(mat, row, column);
		}
	}
}
void GMatrix_scal(Matrix dest, int val){
	for(int row = 0; row < dest.height; row++){
		for(int column = 0; column < dest.width; column++){
			GMAT_AT(dest, row, column) *= val;
		}
	}
}

void GMatrix_prod(Matrix dest, const Matrix mat1, const Matrix mat2){
	GMATH_ASSERT(mat1.width == mat2.height);
	GMATH_ASSERT(dest.height = mat1.height);
	GMATH_ASSERT(dest.width = mat2.width);

	for(int row = 0; row < dest.height; row++){
		for(int column = 0; column < dest.width; column++){
			GMAT_AT(dest, row, column) = 0;
			for(int i=0; i < mat1.width; i++){
				GMAT_AT(dest, row, column) += GMAT_AT(mat1, row, i) * GMAT_AT(mat2, column, i);
			}
		}
	}
}

#endif
