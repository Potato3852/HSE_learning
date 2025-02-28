#include"list.h"
#include<stdio.h>
#include<stdlib.h>

void Add2List(NODE** pphead, int value)
{
    while(*pphead)
    {
        if((*pphead)->value > value)
            break;
        pphead = &((*pphead)->next);
    }
    NODE* pnew = malloc(sizeof(NODE));
    pnew->value = value;
    pnew->next = *pphead;
    *pphead = pnew;
}

void PrintList(NODE* phead)
{
    while(phead)
    {
        printf("%5d", phead->value);
        phead = phead->next;
    }
    printf("\n");
}

NODE* DeleteList(NODE* phead)
{
    if(phead)
    {
        DeleteList(phead->next);
        free(phead);
    }
    return NULL;
}