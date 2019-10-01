//
// Created by rusla on 10/1/2019.
//
// https://gist.github.com/Ogden91/c20403ab09eb638fb288

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>

void formatError();
void displayFile(FILE *, int num, int lineNum);

int main(int ac, char* av[])
{
    char *file = av[1];
    int i, inputNum;
    int lineCount = 0;
    FILE *f;
    if(ac == 1 || ac > 4)
        formatError();
    f= fopen(file, "r");
    // check for open error
    if(f == NULL)
    { printf("Error opening file\n"); exit(1);}

    while((i=fgetc(f))!=EOF)			//count lines
    {
        if (i == '\n')
            lineCount++;
    }
    fseek(f,0, SEEK_SET); 			// go back to start of file
    if( ac == 2)
    {						// when ./tail FILE_NAME
        // diaply whole file if less than 11 lines.
        if(lineCount<=11)
        {
            while((i=fgetc(f))!=EOF)
            { printf("%c", i); }
        }
        else
        {displayFile(f, 10,lineCount);}		// else if greater than 10, use funtion to display last 10 lines.
    }

    else if( ac == 3 )
    {
        char *option = av[2]; // 3rd argument
        if(option[1] == 'v')
        {
            // print out last 10 lines and file name at top
            printf("==> %s <==\n", av[1]);
            displayFile(f,10,lineCount);
        }

        else if(option[1]=='n')
        {
            if(option[2]=='\0')		//check to see if a number exists
                formatError();
            inputNum = atoi(&option[2]);	// get interger value of argument
            displayFile(f,inputNum, lineCount);	//call funtion to display the number of lines from the file
        }
        else
        { formatError(); }
    }
    else if( ac==4 )
    {
        char *option = av[2];
        char *option2 = av[3];

        if((option[1]=='n' && option2[1] == 'v') || (option[1]=='v' && option2[1] == 'n'))
        {
            printf("==> %s <==\n", av[1]);
            if(option[1] == 'n')			// checking to see if argument is -n
            {
                if(option[2]=='\0')			// no numerical value was given
                    formatError();
                inputNum = atoi(&option[2]);
                displayFile(f,inputNum, lineCount);
            }
            else if(option2[1] =='n')			// checking to see of argument is -n
            {
                if(option2[2]=='\0')
                    formatError();			// no numerical value was given
                inputNum = atoi(&option2[2]);		// get integer value
                displayFile(f,inputNum, lineCount);	// call funtion to display file
            }
        }
        else
        { formatError();}
    }
    fclose(f);
    return 0;
}

void formatError()
{
    printf("\nError when reading command...\nUsage:\ntail _FILE_\ntail _FILE_ -v\ntail _FILE_ -n8\ntail _FILE_ -v -n9\ntail _FILE_ -n9 -v\n");
    exit(1);
}

void displayFile(FILE *f,int num, int lineNum)
{
    int i;
    int counter =1;
    lineNum -= num;				// the the line number to start printing from
    int o =0;
    if(lineNum>=1)
    {
        while((i=fgetc(f))!=EOF)
        {
            if(i=='\n')
                counter++;
            if(counter>lineNum)		// start print content when reached line count input by user
            {
                o++;
                if(o>1)
                    printf("%c", i);
            }
        }
    }
    if(lineNum < 0)				// print entire file content
    {
        while((i=fgetc(f))!=EOF)
        {
            printf("%c", i);
        }
    }
}