#ifndef _COMPLEX_H
#define _COMPLEX_H

typedef struct ComplexNumber
{
    double real;
    double imag;
} COMPLEX_NUMBER;

void ComplexInit(COMPLEX_NUMBER* z, double x, double y);
void ComplexPrint(COMPLEX_NUMBER* z);
COMPLEX_NUMBER* ComplexAdd(const COMPLEX_NUMBER* z1, const COMPLEX_NUMBER* z2, COMPLEX_NUMBER* z);
COMPLEX_NUMBER* ComplexMult(const COMPLEX_NUMBER* z1, const COMPLEX_NUMBER* z2,  COMPLEX_NUMBER* z);

#endif

//typedef unsigned long long int ulli; ------- rename type