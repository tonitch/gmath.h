#ifndef GMATH_H
#define GMATH_H
#define PI 3.1415926535

#define GMAT_AT(m, r, c)	((m).mat[(r) * (m).width + (c)])

#include <stdio.h>
#include <math.h>

typedef struct {
	float *mat;
	short width;
	short height;
} Matrix;

typedef float vec3[3];

typedef enum { GMatrix_Rotation_X, GMatrix_Rotation_Y, GMatrix_Rotation_Z} GMatrix_Rotation;

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

void GMatrix_vector_scale(Matrix dest, float x, float y, float z);
void GMatrix_vector_translate(Matrix dest, float x, float y, float z);
void GMatrix_vector_rotate(Matrix dest, float d, GMatrix_Rotation r);

float GVector_dist(const vec3 v1, const vec3 v2);
float GVector_lenght(const vec3 v);
void GVector_cross(vec3 dest, const vec3 v1, const vec3 v2);

void GMatrix_view_translate(Matrix dest, float x, float y, float z);

#endif

#ifdef GMATH_IMPLEMENTATION

#ifndef GMATH_MALLOC
#include <stdlib.h>
#define GMATH_MALLOC malloc
#endif

#ifndef GMATH_MEMCPY
#include <string.h>
#define GMATH_MEMCPY memcpy
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
				GMAT_AT(dest, row, column) += GMAT_AT(mat1, row, i) * GMAT_AT(mat2, i,column);
			}
		}
	}
}

void GMatrix_vector_scale(Matrix dest, float x, float y, float z){
	Matrix trans = GMatrix_unit(4);
	GMAT_AT(trans, 0, 0) = x;
	GMAT_AT(trans, 1, 1) = y;
	GMAT_AT(trans, 2, 2) = z;
	Matrix ret = {.mat=GMATH_MALLOC(sizeof(float)*dest.width*dest.height), .width=dest.width, .height=dest.height};
	GMATH_MEMCPY(ret.mat, dest.mat, sizeof(float)*dest.width*dest.height);
	GMatrix_prod(dest, trans, ret);
	free(ret.mat);
}

void GMatrix_vector_translate(Matrix dest, float x, float y, float z){
	Matrix trans = GMatrix_unit(4);
	GMAT_AT(trans, 0, 3) = x;
	GMAT_AT(trans, 1, 3) = y;
	GMAT_AT(trans, 2, 3) = z;
	Matrix ret = {.mat=GMATH_MALLOC(sizeof(float)*dest.width*dest.height), .width=dest.width, .height=dest.height};
	GMATH_MEMCPY(ret.mat, dest.mat, sizeof(float)*dest.width*dest.height);
	GMatrix_prod(dest, trans, ret);
	free(ret.mat);
}


void GMatrix_vector_rotate(Matrix dest, float d, GMatrix_Rotation r){
	Matrix trans = GMatrix_unit(4);
	switch (r) {
		case GMatrix_Rotation_X:
			GMAT_AT(trans, 1, 1) = cosf(d);
			GMAT_AT(trans, 1, 2) = -sinf(d);
			GMAT_AT(trans, 2, 1) = sinf(d);
			GMAT_AT(trans, 2, 2) = cosf(d);
			break;
		case GMatrix_Rotation_Y:
			GMAT_AT(trans, 0, 0) = cosf(d);
			GMAT_AT(trans, 0, 2) = sinf(d);
			GMAT_AT(trans, 2, 0) = -sinf(d);
			GMAT_AT(trans, 2, 2) = cosf(d);
			break;
		case GMatrix_Rotation_Z:
			GMAT_AT(trans, 0, 0) = cosf(d);
			GMAT_AT(trans, 0, 1) = -sinf(d);
			GMAT_AT(trans, 1, 0) = sinf(d);
			GMAT_AT(trans, 1, 1) = cosf(d);
			break;
	}
	Matrix ret = {.mat=GMATH_MALLOC(sizeof(float)*dest.width*dest.height), .width=dest.width, .height=dest.height};
	GMATH_MEMCPY(ret.mat, dest.mat, sizeof(float)*dest.width*dest.height);
	GMatrix_prod(dest, ret, trans);
	free(ret.mat);
}

float GVector_dist(const vec3 v1, const vec3 v2){
	return GVector_lenght((vec3) { (v1[0] - v2[0]), (v1[1] - v2[1]), (v1[2] - v2[2]) });
}

float GVector_lenght(const vec3 v){
	return sqrtf(powf(v[0], 2) + powf(v[1], 2) + powf(v[2], 2));
}

void GVector_cross(vec3 dest, const vec3 v1, const vec3 v2){
	dest[0] = v1[1] * v2[2] - v1[2]*v2[1];
	dest[1] = v1[2] * v2[0] - v1[0]*v2[2];
	dest[2] = v1[0] * v2[1] - v1[1]*v2[0];
}

void GMatrix_view_lookAt(Matrix dest, vec3 cam_pos, vec3 look_at_pos){
	Matrix trans = GMatrix_unit(4);
	GMatrix_vector_translate(trans, -cam_pos[0], -cam_pos[1], -cam_pos[2]);

	float diff = GVector_dist(cam_pos, look_at_pos);
	vec3 forward_vector = {
		(cam_pos[0] - look_at_pos[0])/diff,
	   	(cam_pos[1] - look_at_pos[1])/diff,
	   	(cam_pos[2] - look_at_pos[2])/diff
	};

	vec3 up = { 0., 1., 0. };
	vec3 left;
	GVector_cross(left, up, forward_vector);
	float left_l = GVector_lenght(left);
	left[0] = left[0]/left_l;
	left[1] = left[1]/left_l;
	left[2] = left[2]/left_l;

	GVector_cross(up, forward_vector, left);
	float rotate_matrix[] = {
		left[0], left[1], left[2], 0,
		up[0], up[1], up[2], 0,
		forward_vector[0], forward_vector[1], forward_vector[2], 0,
		0, 0, 0, 1
	};
	Matrix rotate = {.mat= rotate_matrix, .width=4, .height=4};
	Matrix view = GMatrix_unit(4);
	GMatrix_prod(view, rotate, trans);
	Matrix ret = {.mat=GMATH_MALLOC(sizeof(float)*dest.width*dest.height), .width=dest.width, .height=dest.height};
	GMATH_MEMCPY(ret.mat, dest.mat, sizeof(float)*dest.width*dest.height);
	GMatrix_prod(dest, ret, view);
	free(ret.mat);
}

#endif
