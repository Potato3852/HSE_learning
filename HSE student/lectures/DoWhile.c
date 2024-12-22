#include<stdio.h>

int main()
{
    int low, high;
    scanf("%d %d", &low, &high);

    int sum = 0;
    int current = low;
    do
    {
        sum += current;
        current++;
    }
    while(current <= high);
    printf("Sum = %d\n", sum);
}