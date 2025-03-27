#include "../Header Files/Complex.h"

complex* ComplexCreate(double rp, double cp)
{
	complex* ans = (complex*)malloc(sizeof(complex));
	if (ans == NULL) return;
	ans->rp = rp;
	ans->cp = cp;

	return ans;
}

complex* ComplexSum(complex* n1, complex* n2)
{
	complex* ans = ComplexCreate(n1->rp + n2->rp, n1->cp + n2->cp);

	return ans;
}

complex* ComplexNegate(complex* n1, complex* n2)
{
	complex* ans = ComplexCreate(n1->rp - n2->rp, n1->cp - n2->cp);

	return ans;
}

complex* ComplexMult(complex* n1, complex* n2)
{
	complex* ans = ComplexCreate(n1->rp * n2->rp - n1->cp * n2->cp, n1->rp * n2->cp + n1->cp * n2->rp);

	return ans;
}

complex* ComplexDivide(complex* n1, complex* n2)
{
	complex* ans = ComplexCreate((n1->rp * n2->rp + n1->cp * n2->cp) / (n2->rp * n2->rp + n2->cp * n2->cp), (n1->cp * n2->rp - n1->rp * n2->cp) / (n2->rp * n2->rp + n2->cp * n2->cp));

	return ans;
}

void ComplexPrint(complex* n)
{
	printf("\n%lf + %lfi\n", n->rp, n->cp);
}

void ComplexFree(complex* n)
{
	free(n);
	return;
}