#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv)
{
    int m,n;
    printf("кол-во столбцов: ");
    scanf("%d", &m);
    printf("кол-во строк: ");
    scanf("%d", &n);
    int matrix[n][m];
    int* a = calloc(n*m, sizeof(int));

    for(int i=0; i<n*m; i++)
        scanf("%d", &a[i]);
    printf("\n");
        
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n*m; ++j)
            printf("%d", a[j])
    printf("\n");
    }

    int matrix1[n][m];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            matrix1[i][j] = matrix[j][i];
    printf("\n");

    for(int i= 0; i<n; ++i)
    {
        for(int j=0; j<n ; ++j)
        printf("%d\t", matrix1[i][j]);
    printf("\n");
    }
}