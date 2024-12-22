#ifndef LIST_H
#define LIST_H

typedef struct node
{
    int value;
    struct node* next;
}NODE;

void Add2List(NODE** pphead, int value);
void PrintList(NODE* phead);
NODE* DeleteList(NODE* pphead);

#endif