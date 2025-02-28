#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int findDuplicate(int arr[], int n) {
    int ans = 0;
    for (int i=0; i<n; i++) 
    {
        ans = ans^arr[i];
    }
    for (int i=1; i<n; i++)
    {
        ans = ans^i;
    }
    return ans;
}

int main()
{
    int arr[14] = {1,2,3,4,5,6,7,8,9,10,2,11,12,13};
    int n = 18;
    int x = findDuplicate(arr, n);
    printf("%d", x);
}