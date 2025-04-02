#include "../Header Files/Vector_element.h"
#include "stdio.h"
#include "../Header Files/Complex.h"
#include "../Header Files/Type_info.h"

void type_convert(char* type, data_type* input_type)
{
    if (strcmp(type, "INT") == 0)
    {
        *input_type = INT;
    }
    if (strcmp(type, "DOUBLE") == 0)
    {
        *input_type = DOUBLE;
    }
    if (strcmp(type, "COMPLEX") == 0)
    {
        *input_type = COMPLEX;
    }
    *input_type = -1;
    return;
}

char* toString_Int(void* data)
{
    int value = *(int*)data;
    char* c = malloc(100);
    snprintf(c, 100, "INT,%d", value);
    return c;
}

char* toString_Double(void* data)
{
    double value = *(double*)data;
    char* c = malloc(100);
    snprintf(c, 100, "DOUBLE,%.2lf", value);
    return c;
}

char* toString_Complex(void* data)
{
    complex* value = (complex*)data;
    char* c = malloc(100);
    snprintf(c, 100, "COMPLEX,%.2lf,%.2lf", value->rp, value->cp);
    return c;
}

void* ElementSum(Vector_element e1, Vector_element e2, data_type ans_type)
{
    Vector_element* element1 = malloc(sizeof(Vector_element));
    Vector_element* element2 = malloc(sizeof(Vector_element));
    *element1 = e1;
    *element2 = e2;
    int int_part = 0;
    double double_part = 0;
    double complex_part = 0;
    Vector_element* answer = malloc(sizeof(Vector_element));
    size_t type1 = typeInfo[element1->type];
    data_type type2 = typeInfo[element2->type];

    if (type1 == typeInfo[COMPLEX])
    {
        complex* n = malloc(sizeof(complex));
        n = (complex*)element1->data;
        double_part += n->rp;
        complex_part += n->cp;
        free(n);
    }
    else if (type1 == typeInfo[DOUBLE])
    {
        double* n;
        n = (double*)element1->data;
        double_part += *n;
        free(n);
    }
    else if (type1 == typeInfo[INT])
    {
        int* n;
        n = (int*)element1->data;
        int_part += *n;
        free(n);
    }

    if (type2 == typeInfo[COMPLEX])
    {
        complex* n = malloc(sizeof(complex));
        n = (complex*)element2->data;
        double_part += n->rp;
        complex_part += n->cp;
        free(n);
    }
    else if (type2 == typeInfo[DOUBLE])
    {
        double* n;
        n = (double*)element2->data;
        double_part += *n;
        free(n);
    }
    else if (type2 == typeInfo[INT])
    {
        int* n;
        n = (int*)element2->data;
        int_part += *n;
        free(n);
    }

    if (type1 == typeInfo[COMPLEX] || type2 == typeInfo[COMPLEX]) answer->type = COMPLEX;
    else if (type1 == typeInfo[DOUBLE] || type2 == typeInfo[DOUBLE]) answer->type = DOUBLE;
    else answer->type = INT;
    if (answer->type == COMPLEX)
    {
        complex* n = malloc(sizeof(complex));
        n->rp = double_part + int_part;
        n->cp = complex_part;
        answer->data = n;
        free(n);
    }
    else if (answer->type == DOUBLE)
    {
        double* n;
        *n = double_part + int_part;
        answer->data = n;
        free(n);
    }
    else if (answer->type == INT)
    {
        int* n;
        *n = int_part;
        answer->data = n;
        free(n);
    }
    ans_type = answer->type;
    return answer;
}

void* Element(Vector_element e1, data_type ans_type)
{
    Vector_element* element1 = malloc(sizeof(Vector_element));
    *element1 = e1;
    ans_type = element1->type;
    return element1;
}

size_t typeInfo[] =
{
    [INT] = sizeof(int),
    [DOUBLE] = sizeof(double),
    [COMPLEX] = sizeof(complex)
};