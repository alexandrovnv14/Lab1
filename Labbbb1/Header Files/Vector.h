#ifndef VECTOR_H
#define VECTOR_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../Header Files/Vector_element.h"

typedef struct _Vector
{
	unsigned int dim_count;
	Vector_element* data;
} Vector;

Vector* Create();
void Add(Vector* vector, void* element, data_type type);
void Set(Vector* vector, unsigned int i, void* element, data_type type);
Vector_element Get(Vector* vector, unsigned int i);
void FreeVector(Vector* vector);
void Delete(Vector* vector, unsigned int i);
void* VectorSum(Vector* vector1, Vector* vector2);
void* VectorScalarMult(Vector* vector1, Vector* vector2);

#endif