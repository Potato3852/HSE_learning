#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MIN(a,b) a < b ? a : b

int binary_search(int* arr,int start, int n, int target, char* steps, int *binary_used)
{
    *binary_used = 1;
    int r = n;
    int l = start;
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

int doubling_search(int* arr, int n, int target, char* steps, char* steps1, int* binary_used)
{
    char history[500] = "";
    if(arr[0] == target){
        sprintf(history, "%d(%d) ", arr[0], 0);
        strcat(steps, history);
        return 0;
    }
    
    int step = 1;
    sprintf(history, "%d(%d) ", arr[0], 0);
    strcat(steps, history);

    while(step < n && arr[step] <= target)
    {
        sprintf(history, "%d(%d) ", arr[step], step);
        strcat(steps, history);
        step *= 2;
    }

    if(step >= n || arr[step] == target) {
        sprintf(history, "%d(%d) ", arr[step], step);
        strcat(steps, history);
        return step;
    }

    return binary_search(arr, step/2, MIN(step, n -1), target, steps1, binary_used);
}

int main()
{
    int n, target;
    scanf("%d %d", &n, &target);
    int* arr = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    char binary_history[500] = "";
    char bounds_history[500] = "";
    int binary_used = 0;
    int answer = doubling_search(arr, n, target, bounds_history, binary_history, &binary_used);

    printf("Initial array:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("Target element: %d\n", target);
    printf("Bounds history: %s\n", bounds_history);
    if(binary_used)
        printf("Search history: %s\n", binary_history);
    if(answer != -1)
        printf("Target is found at: %d", answer);
    else
        printf("No targets");
    free(arr);
    return 0;
}
