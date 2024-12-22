#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n,m;
    char c;
    scanf("%d %d", &n, &m);
    long long int* rows = calloc(n, sizeof(long long int));
    long long int* cols = calloc(m, sizeof(long long int));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            long long int a;
            scanf("%lli", &a);
            rows[i] += a;
            cols[j] += a;
        }
    }
    for(int i = 0; i < n; i++)
    {
        printf("%lli ", rows[i]);
    }
    printf("\n");
    for(int i = 0; i < m; i++)
    {
        printf("%lli ", cols[i]);
    }
}