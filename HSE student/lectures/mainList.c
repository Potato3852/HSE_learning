#include<stdio.h>
#include"list.c"
#include<stdlib.h>

int main()
{
    NODE* phead = NULL;
    for(int i = 0; i < 10; i++)
        Add2List(&phead, rand() % 10);
    PrintList(phead);
    phead = DeleteList(phead);
    return 0;
}