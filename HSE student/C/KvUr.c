#include <stdio.h>
#include <math.h>

int main(){
    int a;
    int b;
    int c;
    printf("Enter a\n");
    scanf("%d", &a);
    printf("Enter b\n");
    scanf("%d", &b);
    printf("Enter c\n", &b);
    scanf("%d", &c);
    float d = b*b - 4*a*c;
    if (d >= 0){
        float x1 = (-b - sqrt(d))/(2*a);
        float x2 = (-b + sqrt(d))/(2*a);
        printf("x1 = %f  x2 = %f", x1, x2);
    }
    else{
        printf("NO x");
    }
}