#include <stdio.h>
#include <stdlib.h>

int piv(int* c, int l, int r) 
{ 
    int x = l + (r - l) / 2; 
    int pivot = c[x]; 

    int left = 0, right = 0; 
    int* left1 = (int*)malloc((r - l + 1) * sizeof(int)); 
    int* right1 = (int*)malloc((r - l + 1) * sizeof(int)); 

    for (int i = l; i <= r; i++) 
    { 
        if (i == x) continue; 
        if (c[i] <= pivot) 
        { 
            left1[left++] = c[i]; 
        } 
        else 
        { 
            right1[right++] = c[i]; 
        } 
    } 

    int index = l; 
    for (int i = 0; i < left; i++, index++) 
    { 
        c[index] = left1[i]; 
    } 
    c[index++] = pivot; 
    for (int i = 0; i < right; i++, index++) 
    { 
        c[index] = right1[i]; 
    } 

    free(left1); // Освобождаем память
    free(right1); // Освобождаем память
    return l + left; 
} 

void qsor(int* c, int l, int r, int n) 
{ 
    if (l < r) 
    { 
        int p = piv(c, l, r); 
        int ind = l + (r - l) / 2; 
        printf("\n\nPivot index: %d , pivot element: %d\n", ind, c[p]); 
        printf("Array after partition: "); 
        for (int i = 0; i < n; i++) 
        { 
            printf("%d ", c[i]); 
        } 

        qsor(c, l, p - 1, n); 
        qsor(c, p + 1, r, n); 
    } 
} 

int main() 
{ 
    int n; 

    printf("Enter number of elements: ");
    scanf("%d", &n); // Используем стандартный scanf
    int* c = malloc(n * sizeof(int)); 
    for (int i = 0; i < n; i++) 
    { 
        scanf("%d", &c[i]); // Используем стандартный scanf
    } 
    printf("Initial array:\n"); 
    for (int i = 0; i < n; i++) 
    { 
        printf("%d ", c[i]); 
    } 

    qsor(c, 0, n - 1, n); 

    free(c); // Освобождаем память
    return 0; 
}