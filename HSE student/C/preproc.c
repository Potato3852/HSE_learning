#include <stdio.h>
#include<windows.h>
#include"file1.c"
#include"file2.c"

#define MAX(a,b) a > b ? a : b
#define SQRT(x) x*x 
#include "timer.h"

#define PI 3.14

int main()
{
    int a = 2;
    int b = 3;
    double start, end;
    GET_TIME(start);
    
    printf("%f\n", SQRT(PI));
    printf("%d\n", MAX(a++,b++));
    printf("%d\n", a);
    printf("%d\n", b);
    GET_TIME(end);
    printf("%f\n", end-start);

    return 0;
}