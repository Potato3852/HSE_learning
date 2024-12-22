#include <stdio.h>

int main()
{
    int low, high;
    scanf("%d %d", &low, &high);

    int sum = 0;
    for(int current = low, factor = 1; current<=high; current++, factor*=-1)
        sum += current * factor;
    printf("sum = %d\n", sum);
}