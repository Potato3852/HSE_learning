#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

int main()
{
    int array[SIZE];
    for(int i = 0; i < SIZE; i++)
    {
        int x;
        scanf("%d", &x);
        array[i] = x;
    }
    int flag = 1;
    for(int i = 0; i < SIZE-1; i++)
    {
        if(array[i] < array[i+1])
            flag = 1;
        else
            flag = 0;
    }
    if(flag)
        printf("YES");
    else
        printf("NO");
}