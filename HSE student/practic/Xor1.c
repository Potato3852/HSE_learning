#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int findDuplicate(int arr[], int n) {
    int ans = 0;
    for (int i=0; i<n; i++) 
    {
        ans = ans^arr[i];
    }
    return ans;
}

int main()
{
    int arr[14] = {1,1,2,3,4,5,2,4,5};
    int n = 9;
    int x = findDuplicate(arr, n);
    printf("%d", x);
}