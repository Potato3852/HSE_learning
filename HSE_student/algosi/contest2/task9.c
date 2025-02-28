#include <stdlib.h>
#include <stdio.h>

void insertion_sort(double *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        double key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucket_sort(double *arr, int n)
{
    if (n <= 0) return;

    double min = arr[0];
    double max = arr[0];
    for (int i = 0; i < n; i++) {
        if (max < arr[i]) max = arr[i];
        if (min > arr[i]) min = arr[i];
    }

    double range = max - min;
    if (range == 0) {
        range = 1; // Устанавливаем минимальный диапазон, чтобы избежать деления на ноль
    }

    int numBuckets = n * 2;
    double bucketRange = range / numBuckets;

    double **buckets = (double **)malloc(numBuckets * sizeof(double *));
    int *bucketSizes = (int *)calloc(numBuckets, sizeof(int));

    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = (double *)malloc((n + 1) * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        int bucketIndex = (int)((arr[i] - min) / bucketRange);
        if (bucketIndex == numBuckets) {
            bucketIndex = numBuckets - 1;
        }

        buckets[bucketIndex][bucketSizes[bucketIndex]] = arr[i];
        bucketSizes[bucketIndex]++;
    }

    double *sortedArray = (double *)malloc(n * sizeof(double));
    int index = 0;
    for (int i = 0; i < numBuckets; i++)
    {
        if (bucketSizes[i] > 0)
        {
            printf("Bucket:\n");
            for (int j = 0; j < bucketSizes[i]; j++) {
                printf("%.2f ", buckets[i][j]);
            }

            printf("\n");

            insertion_sort(buckets[i], bucketSizes[i]);

            printf("Sorted bucket:\n");
            for (int j = 0; j < bucketSizes[i]; j++) {
                printf("%.2f ", buckets[i][j]);
                sortedArray[index++] = buckets[i][j];
            }

            printf("\n\n");
        }
    }

    printf("Final array:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", sortedArray[i]);
    }

    printf("\n");

    for (int i = 0; i < numBuckets; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
    free(sortedArray);
}

int main() 
{
    int n;
    scanf("%d", &n);
    double *arr = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }

    printf("Initial array:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n\n");

    bucket_sort(arr, n);
    free(arr);
    return 0;
}