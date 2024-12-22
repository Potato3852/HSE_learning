#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int binary_search(int* arr, int n, int target, char* steps)
{
    int r = n-1;
    int l = 0;
    while(l<=r)
    {
        int mid = l + (r - l) / 2;
        char history[100];
        sprintf(history, "%d(%d) ", arr[mid], mid);
        strcat(steps, history);

        if(arr[mid] == target)
        {
            return mid;
        }
        if(arr[mid] > target)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int n, target;
    scanf("%d %d", &n, &target);
    int* arr = calloc(n, sizeof(int));
    char history[500] = "";

    for(int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        arr[i] = a;
    }

    int answer = binary_search(arr, n, target, history);
    printf("Initial array:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Target element: %d\n", target);
    printf("Search history: %s\n", history);
   if(answer != -1)
   {
    printf("Target is found at: %d", answer);
   }
   else
   {
    printf("No targets");
   }

    return 0;
}

int* arr1 = calloc(2 * n, sizeof(int));
    arr1[n] = pivot;
    int i = 0, j = 0;

    for(int k = 0; k < n; k++)
    {
        if(arr[k])
    }

int pi = p;
    for(int i = p - 1; i>=0; i--)
    {
        if(arr[i] > pivot)
        {
            arr[pi] = arr[i];
            for(int j = i; j < pi - 1; j++)
            {
                arr[j] = arr[j+1];
            }
            pi--;
            arr[pi] = pivot;
        }
    }
    for(int i = pi + 1; i <= end; i++)
    {
        if(arr[i] < pivot)
        {
            arr[pi] = arr[i];
            for(int j = i; j > pi + 1; j--)
            {
                arr[j] = arr[j-1];
            }
            pi++;
            arr[pi] = pivot;
        }
    }