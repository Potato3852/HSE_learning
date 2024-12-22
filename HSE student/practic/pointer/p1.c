#include <stdio.h>

int main() {
int m, n;
printf("Строк: ");
scanf("%d", &m);
printf("Столбцов: ");
scanf("%d", &n);

int matrix[m][n];

printf("Введи матрицу:\n");
for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++)
        scanf("%d", &matrix[i][j]);
}
printf("Наш слоняра\n");
for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++)
        printf("%d ", matrix[i][j]);
    printf("\n");
}

int trans[n][m];
for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++)
        trans[j][i] = matrix[i][j];
}

printf("Транс:\n");
for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++)
        printf("%d ", trans[i][j]);
    printf("\n");
}
}