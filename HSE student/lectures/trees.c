#include "btree.c"
#include<stdio.h>
#include<stdlib.h>

int main()
{
    tree* root = NULL;
    for(int i = 0; i<10; i++)
    {
        int value = rand()%21-10;
        root = Add2Tree(root, value);
        printf("%5d", value);
    }
    printf("\n");
    In(root);
    printf("\n");
    Pre(root);
    printf("\n");
    Post(root);
    printf("\n");
    PrintfTreeOnSide(root, 0);
    DeleteFromTree(root, 6);
    PrintfTreeOnSide(root, 0);
    DeleteFromTree(root, -10);
    DeleteFromTree(root,3);
    PrintfTreeOnSide(root, 0);
    DeleteTree(root);
    return 0;
}