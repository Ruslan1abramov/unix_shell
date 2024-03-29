//
// Created by rusla on 10/1/2019.
// according to http://wetechies.blogspot.com/2013/05/c-implementation-of-wcword-count-linux.html
//
#include<stdio.h>
#include <unistd.h>

int main(int argc , char *argv[])
{
    int character_count = 0;
    int space_count = 0;
    int word_count = 0;
    int line_count = 0;
    char ch;

    FILE *fp;

    if(argc == 0)
    {
        printf("Please specify the filename as argument\n");
        exit(0);
    }

    if(fp != 0)
    {
        printf("No such file or directory\n");
        exit(0);
    }
    fp = fopen(argv[1],"r");

    while((ch=fgetc(fp))!=EOF)
    {
        character_count++;
        if(ch == ' ')
        {
            space_count++;
            word_count++;
        }
        if(ch == '\n')
        {
            line_count++;
        }
    }
    printf("character_count = %d\n",character_count);
    printf("space_count = %d\n",space_count);
    printf("word_count = %d\n",word_count+1);
    printf("line_count = %d\n",line_count);


}