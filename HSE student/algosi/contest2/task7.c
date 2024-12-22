#include<stdio.h>
#include<stdlib.h>

void print_array(int* arr, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int partition(int *arr, int start, int end, int n)
{
    int p = start + (end - start) / 2;
    int pivot = arr[p];

    int left_size = 0, right_size = 0;
    int* left_arr = malloc((end - start + 1) * sizeof(int));
    int* right_arr = malloc((end - start + 1) * sizeof(int));

    for (int i = start; i <= end; i++) {
        if (i == p) continue; 
        if (arr[i] <= pivot) {
            left_arr[left_size++] = arr[i];
        } else {
            right_arr[right_size++] = arr[i];
        }
    }

    int index = start;
    for (int i = 0; i < left_size; i++, index++) {
        arr[index] = left_arr[i];
    }
    arr[index++] = pivot;
    for (int i = 0; i < right_size; i++, index++) {
        arr[index] = right_arr[i];
    }

    free(left_arr);
    free(right_arr);

    return start + left_size;

}

void quick_sort(int* arr, int start, int end, int n)
{
    if(start < end)
    {
        int pivo = partition(arr, start, end, n); // pivo - eto zabavno)
        int pindex = start + ( end - start) / 2;
        
        printf("\n");
        printf("Pivot index: %d , pivot element: %d\n", pindex, arr[pivo]);
        printf("Array after partition: ");
        print_array(arr, n);

        quick_sort(arr, start, pivo - 1, n);
        quick_sort(arr, pivo + 1, end, n);
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

    quick_sort(arr, 0, n-1, n);

    free(arr); 

    return 0;
}