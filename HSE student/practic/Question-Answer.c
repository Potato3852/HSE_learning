#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

struct node* create_linked_list(int val)
{
    struct node* head = malloc(sizeof(struct node));
    head->data = val;
    head->next = NULL;
    return head;
    free(head);
}

int main()
{
    struct node* head = create_linked_list(2);
    printf("%p", head);
  /*struct node one;
    struct node two;
    struct node three;

    one.data = 1;
    two.data = 2;
    three.data = 3;

    one.next = &two;
    two.next = &three;
    three.next = NULL;*/

    return 0;
}