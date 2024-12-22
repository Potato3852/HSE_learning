#include <stdio.h>

int main(){
    //int x = 1;
    //printf("%d\n", x++*++x); /*EBLANSKI CODE*/
    char op;
    scanf("%c", &op);
    int a, b;
    scanf("%d %d", &a, &b);
    if (op == '+')
        printf("%d + %d = %d\n", a, b, a+b);
    else if (op == '-')
        printf("%d - %d = %d\n", a, b, a-b);
    else if (op == '*')
        printf("%d * %d = %d\n", a, b, a*b);
    else if (op == '/')
        printf("%d / %d = %d\n", a, b, a/b);
    else
        printf("You are too stupid to use this program\n");
}