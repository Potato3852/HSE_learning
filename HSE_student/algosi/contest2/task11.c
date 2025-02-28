#include<stdlib.h>
#include<stdio.h>
#define SIZE 21

int arr[SIZE][SIZE][SIZE];

int L(int a, int b, int c)
{
    if(a<=0 || b<= 0 || c<= 0)
        return 1;

    if(a>20 || b>20|| c>20)
        return L(20,20,20);
    
    if(arr[a][b][c] != -1)
        return arr[a][b][c];
    
    if(a<b && b<c)
        arr[a][b][c] = L(a,b,c-1) + L(a,b-1,c-1) - L(a,b-1,c);

    else
        arr[a][b][c] = L(a-1,b,c) + L(a-1,b-1,c) + L(a-1,b,c-1) - L(a-1,b-1,c-1); 
    
    return arr[a][b][c];
}

int main()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                arr[i][j][k] = -1; 
            }
        }
    }
    int a,b,c;
    scanf("%d %d %d", &a,&b,&c);
    printf("%d", L(a,b,c));
    return 0;
}