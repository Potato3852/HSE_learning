#include <stdlib.h>
#include <stdio.h>

double sumArray(double arr[], int size) 
{
    double sum = 0.0; 
    for (int i = 0; i < size; i++) 
    {
        sum += arr[i];
    }
    return sum; 
}

double minArray(double arr[], int size)
{
    double min = 10000000000000.0; 
    for (int i = 0; i < size; i++) 
        min = (arr[i]>min) ? min : arr[i];
    return min; 
}

int com(double arr[], int size, double(*maxArray)(double(arr[]), int size), double(*minArray)(double(arr[]), int size))
{
    double mx,mn;
    mx = maxArray(arr, size);
    mn = minArray(arr, size);
    printf("Крайние элементы: %f, %f", mn, mx);
}

double maxArray(double arr[], int size)
{
    double max = -10000000000000.0; 
    for (int i = 0; i < size; i++) 
        max = (arr[i]<max) ? max : arr[i];
    return max;
}


int main() 
{
    int size;

    printf("Введите размер массива: ");
    scanf("%d", &size);

    double arr[size];
    printf("Введите элементы массива:\n");
    for (int i = 0; i < size; i++)
    {
        printf("Элемент %d: ", i + 1);
        scanf("%lf", &arr[i]);
    }

    double sumA = sumArray(arr, size); 
    printf("Сумма чисел в массиве: %.3f\n", sumA); 

    double minA = minArray(arr, size);
    printf("Минимальный элемент: %.3f\n", minA);

    double maxA = maxArray(arr, size);
    printf("Максимальный элемент: %.3f\n", maxA);

    com(arr, size, maxArray, minArray);

    return 0;
}