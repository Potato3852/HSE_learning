#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void insert(int **newArr, int *n, int index, int value) 
{
    index--;
    *newArr = realloc(*newArr, (*n + 1) * sizeof(int));
    for (int i = *n; i > index; i--) 
    {
        (*newArr)[i] = (*newArr)[i - 1];
    }
    (*newArr)[index] = value;
    (*n)++;
}

void delete(int **newArr, int *n, int index)
{
    index--;
    for (int i = index; i < *n - 1; i++) 
    {
        (*newArr)[i] = (*newArr)[i + 1];
    }
    *newArr = realloc(*newArr, (*n - 1) * sizeof(int));
    (*n)--;
}

void printArr(const int* arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int* arr = calloc(n, sizeof(int));
    for( int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        arr[i] = a;
    }
    int m;
    scanf("%d", &m);

    for(int i = 0; i < m; i++)
    {
        int operation, a, b;
        scanf("%d", &operation);
        if(operation == 0)
        {
            scanf("%d %d", &a, &b);
            insert(&arr, &n, a, b);  
            printArr(arr, n);
            printf("\n");
        }
        if(operation == 1)
        {
            int a;
            scanf("%d", &a);
            delete(&arr, &n, a);  
            printArr(arr, n);
            printf("\n");
        }
    }

    
    free(arr);
}