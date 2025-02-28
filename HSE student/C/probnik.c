#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int minArray(const int* array, int sizeArray)
{
    int min = 10000000;
    for(int i = 0; i < sizeArray; i++)
    {
        if(min > array[i])
            min = array[i];
    }
    return min;
}

int* sortArray(const int* array, int sizeArray)
{
    int* sortedArray = calloc(sizeArray, sizeof(int));
    for(int i = 0; i < sizeArray; i++)
        sortedArray[i] = array[i];  
    for(int j = 0; j < sizeArray; j++)
    {
        for(int i = 0; i < sizeArray; i++)
        {
            if(sortedArray[i] > sortedArray[i+1])
            {   
                sortedArray[i] = sortedArray[i] ^ sortedArray[i+1];
                sortedArray[i+1] = sortedArray[i] ^ sortedArray[i+1];
                sortedArray[i] = sortedArray[i] ^ sortedArray[i+1];
            }
        }
    } 
    return sortedArray; 
}

int main()
{
    int n;
    scanf("%d", &n);
    int* arr = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        arr[i] = x;
    }
    int* sortedArray = sortArray(arr, n);
    for(int i = 1; i < n+1; i++)
    {
        printf("%d ", sortedArray[i]);
    }
    int min = minArray(arr, n);
    printf("\n%d", min);
    free(arr);
    free(sortedArray);
    return 0;
}