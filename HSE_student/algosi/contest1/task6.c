#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int* arr = calloc(n,  sizeof(int));
    for(int i = 0; i < n; i++)
    {
        int a;
        scanf("%i", &a);
        arr[i] = a;
    }
    for(int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d %d", &a, &b);
        c = arr[a];
        arr[a] = arr[b];
        arr[b] = c;
        
    }
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    free(arr);
}