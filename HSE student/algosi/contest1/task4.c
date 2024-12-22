#include<stdio.h>
#include<stdlib.h>
#define min(a,b) a < b ? a : b

int main()
{
    int n;
    scanf("%d", &n);
    int* arrA = calloc(n, sizeof(int));
    int* arrB = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        arrA[i] = a;
    }
    for(int i = 0; i < n; i++)
    {
        int b;
        scanf("%d", &b);
        arrB[i] = b;
    }
    int* arrC = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        int c = min(arrA[i], arrB[i]);
        arrC[i] = c;
    }
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arrC[i]);
    }
}