#include"complex.h"
#include<stdio.h>
#include<stdlib.h>

void ComplexInit(COMPLEX_NUMBER* z, double x, double y)
{
    z->real = x;
    z->imag = y;
}

void ComplexPrint(COMPLEX_NUMBER* z)
{
    printf("Real part = %lf\nImaginary part = %lf\n", z->real, z->imag);
}

COMPLEX_NUMBER* ComplexAdd(const COMPLEX_NUMBER* z1, const COMPLEX_NUMBER* z2,  COMPLEX_NUMBER* z)
{
    z->real = z1->real + z2->real;
    z->imag = z1->imag + z2->imag;
    return z;
}

COMPLEX_NUMBER* ComplexMult(const COMPLEX_NUMBER* z1, const COMPLEX_NUMBER* z2,  COMPLEX_NUMBER* z)
{
    z->real = z1->real * z2->real - z1->imag * z2->imag;
    z->imag = z1->real * z2->imag + z1->imag * z2->real;
    return z;
}