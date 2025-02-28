#include<stdio.h>
#include<stdlib.h>

void print_array(int* arr, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insertion_sort(int* arr, int end)
{
    for(int i = 1; i < end; i++)
    {
        printf("Insertion - Element #%d\n", i);
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key)
            {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        print_array(arr, end);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int* arr = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Initial array:\n");
    print_array(arr, n);

    insertion_sort(arr, n);
    
    return 0;
}