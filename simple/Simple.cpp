//
// Created by rusla on 10/13/2019.
//

//
// Created by rusla on 10/1/2019.
// according to http://www.embhack.com/implementation-of-cat-command/
//

#include<unistd.h> /*for STDOUT_FILENO*/
#include<fcntl.h> /*for open*/
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <utmp.h>

#define FALSE 0
#define TRUE !FALSE

int cat(int argc,char *argv[])
{
    int fd, i, ch;

    for (i = 1; i < argc; i++) {                    /*iterate the loop for total argument count.*/

        fd = open(argv[1],O_RDONLY);            /*open the file in READONLY mode*/

        if(fd < 0) {
            perror("open");
            goto OUT;
        }

        while(read(fd,&ch,1))                   /*Read one byte at a time*/

            write(STDOUT_FILENO,&ch,1);     /*Write the byte on Stdout*/

        close(fd);                              /*close the file discriptor*/
    }

    return 0;
    OUT:
    return -1;
}



extern  int alphasort(); //Inbuilt sorting function

char pathname[MAXPATHLEN];

void die(char *msg)
{
    perror(msg);
    exit(0);
}

int file_select(struct direct *entry)
{
    if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
        return (FALSE);
    else
        return (TRUE);
}

int ls()
{
    int count,i;
    struct direct **files;

    if(!getcwd(pathname, sizeof(pathname)))
        die("Error getting pathname\n");

    printf("Current Working Directory = %s\n",pathname);
    count = scandir(pathname, &files, reinterpret_cast<int (*)(const dirent *)>(file_select), alphasort);

    /* If no files found, make a non-selectable menu item */
    if(count <= 0)
        die("No files in this directory\n");

    printf("Number of files = %d\n",count);
    for (i=1; i<count+1; ++i)
        printf("%s  ",files[i-1]->d_name);
    printf("\n"); /* flush buffer */
}

void formatErrorMv()
{
    printf("Usage:\n./mv foo.txt new.txt\n./mv foot.txt subdir\n");
    exit(1);
}

int mv(int ac, char* av[])
{
    char *file= av[1];
    char *location= av[2];
    char newplace[50];

    if(ac!=3)
        formatErrorMv();
    else
    {
        if(location[0]=='/')				//check to see if input is a path
        {
            strcat(location,"/");			//if argument is a Full Path, prepare to mv to end of path.
            strcat(location,file);
            if(rename(file, location)== 0)
                printf("Successful\n");
            else
                printf("Error:\nDirectory not found\n");
        }
        else
        {
            DIR *isD;
            isD = opendir(location); 				// check if argument is a DIR in CWD

            if(isD==NULL)
            {
                if( rename(file,location)!= 0)
                    printf("Error: File not moved\n");
                else
                    printf("Successful\n");
            }
            else
            {
                char *ptrL;
                ptrL = getcwd(newplace, 50);		// get current working directory path
                strcat(newplace,"/");
                strcat(newplace,location);			// attach mv location to path ptrL
                strcat(newplace,"/");
                strcat(newplace, file);				// keep original file name
                if(rename(file,ptrL)!=-1)
                    printf("Successful\n");
                else
                    printf("Error:\nDirectory not found in CWD\n");
                closedir(isD);
            }
        }
    }
    return 0;
}

void formatErrorTail()
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

int tail(int ac, char* av[])
{
    char *file = av[1];
    int i, inputNum;
    int lineCount = 0;
    FILE *f;
    if(ac == 1 || ac > 4)
        formatErrorTail();
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
                formatErrorTail();
            inputNum = atoi(&option[2]);	// get interger value of argument
            displayFile(f,inputNum, lineCount);	//call funtion to display the number of lines from the file
        }
        else
        { formatErrorTail(); }
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
                    formatErrorTail();
                inputNum = atoi(&option[2]);
                displayFile(f,inputNum, lineCount);
            }
            else if(option2[1] =='n')			// checking to see of argument is -n
            {
                if(option2[2]=='\0')
                    formatErrorTail();			// no numerical value was given
                inputNum = atoi(&option2[2]);		// get integer value
                displayFile(f,inputNum, lineCount);	// call funtion to display file
            }
        }
        else
        { formatErrorTail();}
    }
    fclose(f);
    return 0;
}


int wc(int argc , char *argv[])
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