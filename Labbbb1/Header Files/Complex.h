#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h> 
#include <stdlib.h> 

typedef struct _complex
{
	double rp;
	double cp;
} complex;

complex* ComplexCreate(double rp, double cp);

complex* ComplexSum(complex* n1, complex* n2);

complex* ComplexNegate(complex* n1, complex* n2);

complex* ComplexMult(complex* n1, complex* n2);

complex* ComplexDivide(complex* n1, complex* n2);

void ComplexPrint(complex* c);

void ComplexFree(complex* c);

#endif