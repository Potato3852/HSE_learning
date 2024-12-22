#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE* file = fopen("", "");

    char* str[255] = fgets("", 255, file);

    return 0;
}