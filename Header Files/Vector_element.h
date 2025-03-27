#ifndef VECTOR_ELEMENT_H
#define VECTOR_ELEMENT_H

#include "stdio.h"
#include "stdlib.h" 

typedef enum
{
	INT,
	DOUBLE,
	COMPLEX
} data_type;

typedef struct Vector_element
{
	void* data;
	data_type type;
} Vector_element;

#endif