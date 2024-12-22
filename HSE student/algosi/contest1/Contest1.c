#include <stdio.h>
#include <stdint.h>
int main() 
{
    unsigned long long int ch1 ,ch2;
    unsigned long long int sum;
    scanf("%llu %llu", &ch1, &ch2);

    unsigned int a1 = (ch1 >> 24) & 0xff; 
    unsigned int b1 = (ch1 >> 16) & 0xff;  
    unsigned int c1 = (ch1 >>  8) & 0xff;
    unsigned int d1 = ch1 & 0xff;

    unsigned int a2 = (ch2 >> 24) & 0xff; 
    unsigned int b2 = (ch2 >> 16) & 0xff;  
    unsigned int c2 = (ch2 >>  8) & 0xff;
    unsigned int d2 = ch2 & 0xff;
    unsigned int a3, b3, c3, d3;

    if(a1*a2<=255)
    {
        a3 = a1 * a2;
    }
    else
        a3 = 255;
    if(b1 * b2 <= 255)
    {
        b3 = b1 * b2;
    }
    else
        b3 = 255;
    if(c1 * c2 <= 255)
    {
        c3 = c1 * c2;
    }
    else
        c3 = 255;
    if(d1 * d2 <= 255)
    {
        d3 = d1 * d2;
    }
    else
        d3 = 255;
    
    a3 = a3 << 24;
    b3 = b3 << 16;
    c3 = c3 << 8;
    sum = a3 | b3 | c3 | d3;

    printf("%llu", sum);
    return 0;
}