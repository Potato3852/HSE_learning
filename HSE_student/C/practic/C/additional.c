#include<stdio.h>
#include<stdlib.h>

char* printThisMessage(void)
{
    char *arr = calloc(100, sizeof(char));
    printf("Hello, world!");
    free(arr);
}