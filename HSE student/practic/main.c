#include <stdio.h>
#include <string.h>
#include "additional.c"

struct tom{
};
struct bob{
    void(*printThisMessage);
};
int main()
{
    printThisMessage();
}