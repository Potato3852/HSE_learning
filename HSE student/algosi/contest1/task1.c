#include <stdio.h>
#include <stdint.h>

int main()
{
    unsigned long long a, b;
    scanf("%llu %llu", &a, &b);
    unsigned long long int sum = 0;
    for (int i = 0; i < 4; i++) {
        int ch1 = (a >> (i * 8)) & 0xFF; 
        int ch2 = (b >> (i * 8)) & 0xFF; 
        int ans = (int)ch1 * (int)ch2; 
        if (ans > 255) {
            ans = 255;
        }
        sum = sum | (ans << (i * 8));
    }
    printf("%llu\n", sum); 
    return 0;
}