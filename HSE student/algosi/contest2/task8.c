#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000
#define HEX 16
#define MAX_LENGTH 16

int num16(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('A' <= c && c <= 'F') return c - 'A' + 10;
    else if ('a' <= c && c <= 'f') return c - 'a' + 10;
    return -1;
}

void count_sort(unsigned long long arr[], int size, unsigned long long exp) {
    unsigned long long output[SIZE];
    int count[HEX] = {0};

    for (int i = 0; i < size; ++i)
    {
        count[(arr[i] / exp) % HEX]++;
    }

    for (int i = 1; i < HEX; ++i)
    {
        count[i] += count[i - 1];
    }

    for (int j = size - 1; j >= 0; --j)
    {
        output[count[(arr[j] / exp) % HEX] - 1] = arr[j];
        count[(arr[j] / exp) % HEX]--;
    }

    for (int j = 0; j < size; ++j)
    {
        arr[j] = output[j];
    }
}

void radix_sort(unsigned long long arr[], int size, int max_k)
{
    unsigned long long max = arr[0];
    for (int j = 0; j < size; ++j)
    {
        if (max < arr[j])
        {
            max = arr[j];
        }
    }

    for (unsigned long long exp = 1; max / exp > 0; exp *= HEX)
    {
        printf("Sorting by %d digit:\n", max_k);
        count_sort(arr, size, exp);
        for (int j = 0; j < size; ++j)
        {
            printf("%llX\n", arr[j]);
        }
        printf("\n");
        max_k--;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int max_k = 0;
    unsigned long long arr[n];
    for (int j = 0; j < n; ++j)
    {
        char hex[MAX_LENGTH];
        scanf("%15s", hex);

        if(max_k < strlen(hex))
            max_k = strlen(hex) - 1;

        unsigned long long num = strtoll(hex, NULL, HEX);
        arr[j] = num;
    }

    radix_sort(arr, n, max_k);
    return 0;
}