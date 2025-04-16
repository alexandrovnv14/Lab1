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
    char* c = (char*)malloc(100);
    snprintf(c, 20, "INT,%d", value);
    return c;
}

char* toString_Double(void* data)
{
    double value = *(double*)data;
    char* c = (char*)malloc(100);
    snprintf(c, 20, "DOUBLE,%.2lf", value);
    return c;
}

char* toString_Complex(void* data)
{
    complex* value = (complex*)data;
    char* c = (char*)malloc(100);
    snprintf(c, 20, "COMPLEX,%.2lf,%.2lf", value->rp, value->cp);
    return c;
}

Vector_element* ElementSum(Vector_element e1, Vector_element e2, data_type* ans_type)
{
    Vector_element* element1 = (Vector_element*)malloc(sizeof(Vector_element));
    Vector_element* element2 = (Vector_element*)malloc(sizeof(Vector_element));
    *element1 = e1;
    *element2 = e2;
    int int_part = 0;
    double double_part = 0;
    double complex_part = 0;
    Vector_element* answer = (Vector_element*)malloc(sizeof(Vector_element));
    if (answer == NULL)
        return -1;
    size_t type1 = typeInfo[element1->type];
    size_t type2 = typeInfo[element2->type];

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
        double* n = (double*)malloc(sizeof(double));
        *n = *(double*)element1->data;
        double_part += *n;
        printf("%f\n", double_part);
        free(n);
    }
    else if (type1 == typeInfo[INT])
    {
        int* n = (int*)malloc(sizeof(int));
        *n = *(int*)element1->data;
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
        double* n = (double*)malloc(sizeof(double));
        *n = *(double*)element2->data;
        double_part += *n;
        printf("%f\n", double_part);
        free(n);
    }
    else if (type2 == typeInfo[INT])
    {
        int* n = (int*)malloc(sizeof(int));
        *n = *(int*)element2->data;
        int_part += *n;
        free(n);
    }

    if (type1 == typeInfo[COMPLEX] || type2 == typeInfo[COMPLEX]) answer->type = COMPLEX;
    else if (type1 == typeInfo[DOUBLE] || type2 == typeInfo[DOUBLE]) answer->type = DOUBLE;
    else answer->type = INT;
    if (answer->type == COMPLEX)
    {
        complex* n = (complex*)malloc(sizeof(complex));
        if (n == NULL)
            return -1;
        n->rp = double_part + int_part;
        n->cp = complex_part;
        answer->data = malloc(sizeof(complex));
        memcpy(answer->data, n, sizeof(complex));
        free(n);
    }
    else if (answer->type == DOUBLE)
    {
        double* n = (double*)malloc(sizeof(double));
        *n = double_part;
        answer->data = (void*)n;
    }
    else if (answer->type == INT)
    {
        int* n = (int*)malloc(sizeof(int));
        *n = int_part;
        answer->data = n;
    }
    *ans_type = answer->type;
    return answer;
}

Vector_element* ElementMult(Vector_element e1, Vector_element e2, data_type* ans_type)
{
    Vector_element* element1 = (Vector_element*)malloc(sizeof(Vector_element));
    Vector_element* element2 = (Vector_element*)malloc(sizeof(Vector_element));
    *element1 = e1;
    *element2 = e2;
    int int1 = 0;
    int int2 = 0;
    double double1 = 0;
    double double2 = 0;
    double complex1 = 0;
    double complex2 = 0;
    Vector_element* answer = (Vector_element*)malloc(sizeof(Vector_element));
    if (answer == NULL)
        return -1;
    size_t type1 = typeInfo[element1->type];

    size_t type2 = typeInfo[element2->type];

    if (type1 == typeInfo[COMPLEX])
    {
        complex* n;
        n = (complex*)element1->data;
        double1 = n->rp;
        complex1 = n->cp;
        free(n);
    }
    else if (type1 == typeInfo[DOUBLE])
    {
        double* n = (double*)malloc(sizeof(double));
        *n = *(double*)element1->data;
        double1 = *n;
        printf("%f\n", double1);
        free(n);
    }
    else if (type1 == typeInfo[INT])
    {
        int1 = *(int*)element1->data;
    }

    if (type2 == typeInfo[COMPLEX])
    {
        complex* n;
        n = (complex*)element2->data;
        double2 = n->rp;
        complex2 = n->cp;
        free(n);
    }
    else if (type2 == typeInfo[DOUBLE])
    {
        double* n = (double*)malloc(sizeof(double));
        *n = *(double*)element2->data;
        double2 = *n;
        printf("%f\n", double2);
        free(n);
    }
    else if (type2 == typeInfo[INT])
    {
        int2 = *(int*)element2->data;
    }
    if (double1 == 0 && double2 == 0 && complex1 == 0 && complex2 == 0)
    {
        answer->data = malloc(sizeof(int));
        answer->type = INT;
        *(int*)answer->data = int1 * int2;
    }
    else if (complex1 == 0 && complex2 == 0)
    {
        answer->data = malloc(sizeof(double));
        answer->type = DOUBLE;
        *(double*)answer->data = double1 * double2;
    }
    else
    {
        double1 += int1;
        double2 += int2;
        answer->type = COMPLEX;
        complex* n = (complex*)malloc(sizeof(complex));
        if (n == NULL)
            return -1;
        n->rp = double1 * double2 - complex1 * complex2;
        n->cp = complex1 * double2 + double1 * complex2;
        answer->data = malloc(sizeof(complex));
        memcpy(answer->data, n, sizeof(complex));
        free(n);
    }
    *ans_type = answer->type;
    return answer;
}

void* Element(Vector_element e1, data_type* ans_type)
{
    Vector_element* element1 = malloc(sizeof(Vector_element));
    element1 = &e1;
    *ans_type = element1->type;
    return element1; 
}

size_t typeInfo[] =
{
    [INT] = sizeof(int),
    [DOUBLE] = sizeof(double),
    [COMPLEX] = sizeof(complex)
};