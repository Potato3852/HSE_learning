#include <stdio.h>
#include <string.h>

char word1[32] = "";

void Bin(long long int n, long long int *prevBit, int *prevAdded) {
    if (n > 0) {
        long long int bit = n % 2;
        Bin(n / 2, prevBit, prevAdded); 
        if (*prevAdded == 0 || *prevBit != bit)
        {
            if (bit == 1)
                strcat(word1, "1");
            else
                strcat(word1, "0");
            *prevAdded = 1;
        }
        else
            *prevAdded = 0; 
        *prevBit = bit;
    }
}

void reverse(char str[])
{
    int start = 0;
    int end = strlen(str) - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    long long int n;
    scanf("%lld", &n);

    long long int prevBit = -1;
    int prevAdded = 0;

    Bin(n, &prevBit, &prevAdded);
    printf("%s\n", word1);
    
    reverse(word1);
    printf("%s", word1);
    return 0;
}