#include<stdio.h>
#include<stdlib.h>

void line_search(int* arr, int n, int target)
{
    int flag = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i]==target)
        {
            flag++;
            break;
        }
    }
    if(flag == 0)
    {
        printf("\nNo targets");
    }
    else
    {
        printf("\nTarget is found at: ");
        for(int i = 0; i < n; i++)
        {
            if(arr[i]==target)
            {
                printf("%d ", i);
            }
        }
    }
}

int main()
{
    int n, target;
    scanf("%d %d", &n, &target);


    int* arr = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Initial array:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    printf("\nTarget element: %d", target);

    line_search(arr, n, target);

    return 0;
}