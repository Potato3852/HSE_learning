#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int l, int r, int mid) {
    int nL = mid - l + 1;
    int nR = r - mid;

    int* left = calloc(nL, sizeof(int));
    int* right = calloc(nR, sizeof(int));

    for (int i = 0; i < nL; i++) {
        left[i] = arr[l + i];
    }

    for (int j = 0; j < nR; j++) {
        right[j] = arr[mid + 1 + j];
    }

    printf("Left part: ");
    for (int i = 0; i < nL; i++) {
        printf("%d ", left[i]);
    }

    printf("\nRight part: ");
    for (int j = 0; j < nR; j++) {
        printf("%d ", right[j]);
    }
    printf("\n");

    int indexL = 0, indexR = 0, index = l;

    while (indexL < nL && indexR < nR) {
        if (left[indexL] < right[indexR]) {
            arr[index] = left[indexL];
            indexL++;
        } else {
            arr[index] = right[indexR];
            indexR++;
        }
        index++;
    }
    while (indexL < nL) {
        arr[index] = left[indexL];
        indexL++;
        index++;
    }
    while (indexR < nR) {
        arr[index] = right[indexR];
        indexR++;
        index++;
    }

    printf("Merged parts: ");
    for (int i = l; i <= r; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    free(left);
    free(right);
}

void merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int mid = (l + r - 1) / 2;

        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);

        merge(arr, l, r, mid);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Initial array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    merge_sort(arr, 0, n - 1);

    free(arr);
    return 0;
}