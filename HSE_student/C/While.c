#include <stdio.h>

int main()
{
    int low, high;
    scanf("%d %d", &low, &high);
    int sum = 0;
    int current = low;
    while(current <= high)
    {
        sum += current;
        current++;
    }
    printf("Sum = %d\n", sum);
}