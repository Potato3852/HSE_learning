#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int* arrTrue = calloc(n, sizeof(int));
    for(int i = 0; i < n-1; i++)
    {
        int a;
        scanf("%d", &a);
        arrTrue[a-1]++;
    }
    for(int i = 0; i < n; i++)
    {
        if(arrTrue[i]==0)
            printf("%d", i+1);
    }
}