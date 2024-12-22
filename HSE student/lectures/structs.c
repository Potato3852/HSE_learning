#include<stdio.h>
#include<stdlib.h>
#include"complex.c"


struct S1
{
    int x;
};
struct S2
{
    int x;
    double y;
};
struct S3
{
    int x;
    char y;
    double z;
}; 

int main()
{
    COMPLEX_NUMBER z1 = {z1.real = 4.2, z1.imag = 5.9};
    COMPLEX_NUMBER z2 = {z2.real = 1.2, z2.imag = 2.9};
    COMPLEX_NUMBER z = {z.real = 0, z.imag = 0};
    ComplexAdd(&z2, &z1, &z);
    ComplexPrint(&z);
    COMPLEX_NUMBER zen = {z.real = 0, z.imag = 0};
    ComplexMult(&z1, &z2, &zen);
    ComplexPrint(&zen);
}
//printf("%llu \n", sizeof(struct S1));
//printf("%llu \n", sizeof(struct S2));
//printf("%llu \n", sizeof(struct S3));