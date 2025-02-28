#include <stdio.h>

int main()
{
    char ch;
    int ndigits[10];
    for(int i = 0; i<10; i++)
        ndigits[i] = 0;
    while((ch = getchar()) != 'e')
    {
        switch(ch){
            case '0':
            case '1': 
            case '2': 
            case '3': 
            case '4': 
            case '5': 
            case '6': 
            case '7': 
            case '8': 
            case '9':
                ndigits[ch - '0']++;
                break;
        }
    }
    for(int i = 0; i<10; i++)
        printf("%d: %d\n", i, ndigits[i]);
}