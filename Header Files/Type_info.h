#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include "stdlib.h"
#include "Complex.h"


char* toString_Int(void* data);

char* toString_Double(void* data);

char* toString_Complex(void* data);

void* ElementSum(Vector_element* element1, Vector_element* element2);

void type_convert(char* type, data_type* input_type);

extern size_t typeInfo[];

#endif