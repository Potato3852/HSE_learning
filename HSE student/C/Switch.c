#include <stdio.h>

int main()
{
    char op;
    scanf("%c", &op);
    int a, b;
    scanf("%d %d", &a, &b);
    switch(op)
    {
        case '+':
            printf("%d + %d = %d\n", a, b, a+b);
            break;
        case '-':
            printf("%d - %d = %d\n", a, b, a-b);
            break;
        case '*':
            printf("%d * %d = %d\n", a, b, a*b);
            break;
        case '/':
            printf("%d / %d = %d\n", a, b, a/b);
            break;
        default:
            printf("Srupid!\n");
    }   
}