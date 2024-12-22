#include<stdlib.h>
#include<stdio.h>

int main()
{
    int n, m;
    scanf("%d", &n);
    int* arr = calloc(n, sizeof(int));
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        sum += a;
        arr[i] = sum;
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++)
    {
        int p;
        scanf("%d", &p);
        int l = 0, r = n-1;
        while(l < r)
        {
            int mid = l + (r - l) /2;
            if(arr[mid] < p)
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        printf("%d\n", l+1);
    }
    return 0;
}