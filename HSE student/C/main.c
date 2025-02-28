#include<stdio.h>

#define TASK2
#define MAX_LENGHT 100

#ifdef TASK1

int main(int argc, char* argv[])
{
    FILE* fr = fopen(argv[1], "rt");
    FILE* fw = fopen(argv[2], "wt");
    if(!fr)
    {
        fprintf(stderr, "Error to read\n");
        return -1;
    }
    if(!fw)
    {
        fprintf(stderr, "Error to write\n");
        fclose(fr);
        return -1;
    }
    char str(MAX_LENGHT) = {0};
    while(!feof(fr))
    {
        fgets(str, MAX_LENGHT, fr);
        printf("%s", str);
        fputs(str, fw);
    }
    fclose(fr);
    fclose(fw);
    return 0;
}

#endif

#ifdef TASK2

#define MAX_LENGHT 100

int shifr(char* input, char* output)
{
    FILE* fr = fopen(input, "rb");
    if(!fr)
    {
        fprintf(stderr, "Error to read\n");
        return -1;
    }
    FILE* fw = fopen(output, "wb");
    if(!fw)
    {
        fprintf(stderr, "Error to write\n");
        fclose(fr);
        return -1;
    }
    fseek(fr, 0, SEEK_END);
    long len = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    unsigned char key = 1;
    for(int i = 0; i < len; i++)
    {
        unsigned char c = fgetc(fr);
        unsigned char res = c ^ key++;
        fputs(res, fw);
    }
    fclose(fr);
    fclose(fw);
}

int main(int argc, char** argv)
{
    if(argc < 4)
        fprintf(stderr, "You are wrong\n");
    shifr(argv[1], argv[2]);
    shifr(argv[2], argv[3]);
    return 0;
}

#endif