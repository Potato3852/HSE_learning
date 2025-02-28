#include <stdio.h>
#include <stdlib.h>

float DET(float **matrix, int n) 
{
    float det = 0;
    int i, j, k;
    float **temp;

    if (n == 1) {
        return matrix[0][0];
    } else if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        det = 0;
        for (k = 0; k < n; k++) {
            temp = (float **)malloc((n-1) * sizeof(float *));
            for (i = 0; i < n-1; i++) 
                temp[i] = (float *)malloc((n-1) * sizeof(float));

            for (i = 1; i < n; i++) {
                for (j = 0; j < n; j++) {
                    if (j < k) {
                        temp[i-1][j] = matrix[i][j];
                    } else if (j > k) 
                        temp[i-1][j-1] = matrix[i][j];
                }
            }

            det += matrix[0][k] * DET(temp, n-1) * (k%2 == 0 ? 1 : -1);

            for (i = 0; i < n-1; i++) 
                free(temp[i]);
            free(temp);
        }
    }
    return det;
}

int main(int argc, char** argv) {
    int n, i, j;
    float **mat;
    printf("Кол-во строк в квадратной матрице: ");
    scanf("%d", &n);
    mat = (float **)malloc(n * sizeof(float *));
    for (i = 0; i < n; i++) {
        mat[i] = (float *)malloc(n * sizeof(float));
    }
    printf("Введите матрицу:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) 
            scanf("%f", &mat[i][j]);
    }
    float det = DET(mat, n);
    printf("Определитель равен: %.2f\n", det);

    for (i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}