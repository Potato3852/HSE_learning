#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char name[255];
    char sinonim[255];
};

int main()
{
    int n;
    scanf("%d", &n);
    struct node* voc = malloc(2 * n * sizeof(struct node*));
    for(int i = 0; i < n; i++)
    {
        char* a[255];
        char* b[255];
        scanf("%s %s", &a, &b);
        struct node word1 = {a, b};
        struct node word2 = {b, a};
        voc[i] = word1;
        voc[n-i] = word2;
    }
    char* key[255];
    scanf("%s", &key);
    for(int i = 0; i < 2*n; i++)
    {
        if(voc[i].name == key)
        {
            printf("%s", voc[i].sinonim);
        }
    }
    return 0;
}