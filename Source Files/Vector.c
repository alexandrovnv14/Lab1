#include "../Header Files/Vector.h"
#include "../Header Files/Complex.h"
#include "../Header Files/Vector_element.h"
#include "../Header Files/Type_info.h"

Vector* Create()
{
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	if (!vector) return NULL;
	vector->dim_count = 0;
	vector->data = NULL;
	return vector;
}

void Add(Vector* vector, void* element, data_type type)
{
	size_t size = typeInfo[type];
	vector->dim_count++;
	vector->data = (Vector_element*)realloc(vector->data, vector->dim_count * sizeof(Vector_element));
	if (vector->data == NULL) return;
	vector->data[vector->dim_count - 1].data = malloc(size);
	memcpy(vector->data[vector->dim_count - 1].data, element, size);
	vector->data[vector->dim_count - 1].type = type;
}

Vector_element Get(Vector* vector, unsigned int i)
{
	if (!vector || i >= vector->dim_count)
	{
		return;
	}
	Vector_element v_e = vector->data[i];
	return v_e;
}

void Set(Vector* vector, unsigned int i, void* element, data_type type)
{
	size_t size = typeInfo[type];
	if (!vector || i >= vector->dim_count)
		return;
	free(vector->data[i].data);
	vector->data[i].data = malloc(size);
	memcpy(vector->data[i].data, element, size);
	vector->data[i].type = type;
}

void Delete(Vector* vector, unsigned int i)
{
	if (!vector || i >= vector->dim_count)
		return;
	free(vector->data[i].data);
	memmove(&vector->data[i], &vector->data[i + 1], (vector->dim_count - i - 1) * sizeof(Vector_element));
	vector->dim_count--;
	vector->data = (Vector_element*)realloc(vector->data, vector->dim_count * sizeof(Vector_element));
}

void FreeVector(Vector* vector)
{
	if (!vector)
		return;
	for (unsigned int i = 0; i < vector->dim_count; i++)
	{
		free(vector->data[i].data);
	}
	free(vector->data);
	free(vector);
}

void* VectorSum(Vector* vector1, Vector* vector2)
{
	int i1 = vector1->dim_count;
	int i2 = vector2->dim_count;
	Vector* answer = malloc(sizeof(Vector));
	for (int i = 0; i < min(i1,i2); i++)
	{
		Add(answer, ElementSum(Get(vector1,i))
	}
}