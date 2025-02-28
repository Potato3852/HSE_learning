#include <stdio.h> 
#include <stdlib.h> 
 
long long int zero(long long int* arr, long long int n)
{
    long long int ans = 0;
    for(long long int i = 0; i < n; i++) {
        if(arr[i] == 0)
            ans++;
    }
    return ans;
}
 
void worst_case(long long int* comands, long long int* zeros, long long int n) 
{
    long long int right = n+1; 
    long long int left = -1; 
    while (left < n && right > 0) 
    { 
        right--; 
        left++; 
        
        long long int count_zero = zero(zeros, n);  
        
        if (comands[left] == 1) 
        {    
            long long int x1 = 0; 
            for (long long int i = 0; i < n && x1 == 0; i++)
            { 
                if (zeros[i] == 0)
                { 
                    zeros[i] = right; 
                    x1++; 
                } 
            } 
        } 
        
        if (comands[left] == -1) 
        { 
            long long int no_x = 0; 
            for (long long int i = n - 1; i >= 0 && no_x == 0; i--)
            { 
                if (zeros[i] == 0) 
                { 
                    zeros[i] = right; 
                    no_x++; 
                } 
            }

        } 

        if (comands[left] == 0) 
        { 
            long long int k0 = count_zero / 2; 
            long long int number = 0; 
            long long int x0 = 0; 
            for (int i = n - 1; i >= 0 && x0 == 0; i--){ 
                if (zeros[i] == 0 && number >= k0) 
                { 
                    zeros[i] = right; 
                    x0++; 
                } 

                if (zeros[i] == 0) 
                    number++; 
            } 
        }
    } 
    for (long long int i = 0; i < n; i++) 
        printf("%lld ", zeros[i]);

} 
    
    
int main() 
{ 
    long long int n;

    scanf("%lld", &n);

    long long int* comands = calloc(n, sizeof(long long int));
    for (long long int i = 0; i < n; i++) 
        scanf("%lld", &comands[i]); 

    long long int* zeros = calloc(n, sizeof(long long int)); //черновик массива, служащего плохим случаем.
    
    worst_case(comands, zeros, n); 
    
    return 0; 
}