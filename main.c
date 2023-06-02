#define GMATH_IMPLEMENTATION
#include "gmath.h"
#include <stdio.h>


int main(void)
{
	Matrix trans = GMatrix_unit(4); 
	GMatrix_print(trans);
	printf("----------------------------------------\n");

	GMatrix_vector_translate(trans, 2, 3 ,4); 
	GMatrix_print(trans);
	printf("----------------------------------------\n");

	GMatrix_vector_scale(trans, 2, 1 ,0.5); 
	GMatrix_print(trans);
	printf("----------------------------------------\n");

	GMatrix_vector_rotate(trans, PI* 0.5, GMatrix_Rotation_X); 
	GMatrix_print(trans);
	printf("----------------------------------------\n");

	GMatrix_vector_rotate(trans, PI, GMatrix_Rotation_Y); 
	GMatrix_print(trans);
	printf("----------------------------------------\n");
}
