#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LENGHT 100

int str_len(const char* str)
{
    int len = 0;
    while(str[len++]!=0);
    return len - 1;
}

void str_cpy_sigma(char* dest, const char* source)
{
    while(*dest++ = *source++);  //подумать вечером
}

void str_cat(char* dest, const char* source)
{
    while(*dest++);
    str_cpy_sigma(dest-1, source);
}

int str_cmp(const char* s1, const char* s2)
{
    while(*s1 && *s2)
    {
        if(*s1 > *s2)
            return 1;
        else if(*s1 < *s2)
            return -1;
        s1++;
        s2++;
    }
    if(*s1)
        return 1;
    if(*s2)
        return -1;
    return 0;
}

int main()
{
    const char* str = "Hello, world!";
    char s1[MAX_LENGHT] = "Hello";
    printf("%d\n", str_cmp(str,s1));
    return 0;
}