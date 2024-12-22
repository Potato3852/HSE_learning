#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int* arr = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        arr[i] = a;
    }
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", arr[n-i]);
    }
}