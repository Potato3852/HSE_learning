#include<stdio.h>

enum COLOR{RED, WHITE, BLUE};
enum MATERIAL{RUBBER, WOOD, IRON};

union U
{
    int x;
    double y;
    char z;
};

struct S
{
    int x;
    double y;
    char z;
};

union U1
{
    int x;
    float y;
    double z;
};

int main()
{
    printf("%llu\n", sizeof(struct S));
    printf("%llu\n", sizeof(union U));
};