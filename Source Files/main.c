#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../Header Files/Vector.h"
#include "../Header Files/Complex.h"
#include "../Header Files/Vector_element.h"
#include "../Header Files/Type_info.h"

void save(Vector* vector, FILE* output)
{
	for (unsigned int i = 0; i < vector->dim_count; i++)
	{
		Vector_element element = vector->data[i];
		char* dim;
		data_type type = element.type;
		if (typeInfo[type] == typeInfo[INT]) dim = toString_Int(element.data);
		else if (typeInfo[type] == typeInfo[DOUBLE]) dim = toString_Double(element.data);
		else if (typeInfo[type] == typeInfo[COMPLEX]) dim = toString_Complex(element.data);
		else
		{
			printf("ERROR: unknown type: %zu\n", typeInfo[type]);
			continue;
		};
		fprintf(output, "%s\n", dim);
	}
	return;
}

void* type_scan(FILE* input, char* type, data_type* input_type)
{
	if (strcmp(type, "INT") == 0)
	{
		int* value = malloc(sizeof(int));
		fscanf(input, "%d", value);
		*input_type = INT;
		return value;
	}
	if (strcmp(type, "DOUBLE") == 0)
	{
		double* value = malloc(sizeof(double));
		fscanf(input, "%lf", value);
		*input_type = DOUBLE;
		return value;
	}
	if (strcmp(type, "COMPLEX") == 0)
	{
		double rat, com;
		fscanf(input, "%lf,%lf", &rat, &com);
		complex* value = ComplexCreate(rat, com);
		*input_type = COMPLEX;
		return value;
	}
	*input_type = -1;
	return NULL;
}

int main()
{
	FILE* input = fopen("test.txt", "r");
	FILE* output = fopen("output.txt", "w");
	
	Vector* vector = Create();

	if (!input)
	{
		printf("ERROR: input file not found");
		return 1;
	}
	if (!output)
	{
		printf("ERROR: output file not found");
		return 1;
	}
	int dim_count;
	fscanf(input, " %d\n", &dim_count);
	for (int i = 0; i < dim_count; i++)
	{
		char type[50];
		fscanf(input, " %[^,],", type);
		data_type d_type;
		void* data = type_scan(input, type, &d_type);
		if (!data)
		{
			printf("ERROR: var type not declared");
			return 1;
		}
		Add(vector, data, d_type);
	}
	unsigned int key_count;
	fscanf(input, " %d", &key_count);
	for (unsigned int i = 0; i < key_count; i++)
	{
		char key[50];
		fscanf(input, " %[^,],", key);
		printf("Command: %s\n", key);
		if (strcmp(key, "ADD") == 0)
		{
			char type[20];
			fscanf(input, " %[^,],", type);
			data_type d_type;
			void* data = type_scan(input, type, &d_type);
			Add(vector, data, d_type);
			printf("ADDED\n");
		}
		else if (strcmp(key, "SET") == 0)
		{
			char type[20];
			int i;
			fscanf(input, " %d:%[^,],", &i, type);
			printf("%d", i);
			data_type d_type;
			void* data = type_scan(input, type, &d_type);
			Set(vector, i, data, d_type);
			printf("SET\n");
		}
		else if (strcmp(key, "GET") == 0)
		{
			char input_type[20];
			int i;
			fscanf(input, " %[^,],%d,", input_type, &i);
			data_type type;
			type_convert(input_type, &type);
			Vector_element* v_e = mallox(sizeof(Vector_element));
			*v_e = Get(vector, i);
			void* data = v_e->data;
			char* dim;
			if (typeInfo[type] == typeInfo[INT]) dim = toString_Int(data);
			else if (typeInfo[type] == typeInfo[DOUBLE]) dim = toString_Double(data);
			else if (typeInfo[type] == typeInfo[COMPLEX]) dim = toString_Complex(data);
			else
			{
				printf("ERROR: unknown type: %zu\n", typeInfo[type]);
				continue;
			};
			printf("GOT %s %d: %s\n", type, i, dim);
		}
		else if (strcmp(key, "DELETE") == 0)
		{
			int i;
			fscanf(input, "%d", &i);
			Delete(vector, i);
			printf("DELETED\n");
		}
		else
		{
			printf("ERROR: unknown command");
			return 1;
		}
		
	}
	save(vector, output);
	fclose(input);
	fclose(output);
	FreeVector(vector);

	return 0;
}