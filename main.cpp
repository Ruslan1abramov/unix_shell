// C Program to design a shell in Linux
//https://www.geeksforgeeks.org/making-linux-shell-c/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 

// Clearing the shell using escape sequences 
#define clear() printf("\033[H\033[J")

// Greeting shell during startup 
void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
           "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
           "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}

// Function to take input 
int takeInput(char* str)
{
    char* buf;

    buf = readline("\n>>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

// Function to print Current Directory. 
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

// Help command builtin 
void openHelp()
{
    puts("\n***WELCOME TO MY SHELL HELP***"
         "\nCopyright @ Suprotik Dey"
         "\n-Use the shell at your own risk..."
         "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>all other general commands available in UNIX shell"
         "\n>pipe handling"
         "\n>improper space handling");

    return;
}

// Function to execute builtin commands 
int ownCmdHandler(char** parsed)
{
    int NoOfOwnCmds = 14, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    //simple
    ListOfOwnCmds[4] = "ws";
    ListOfOwnCmds[5] = "cat";
    ListOfOwnCmds[6] = "ls";
    ListOfOwnCmds[7] = "mv";
    //admin
    ListOfOwnCmds[8] = "chmod";
    ListOfOwnCmds[9] = "chown";
    ListOfOwnCmds[10] = "adduser";
    //sys
    ListOfOwnCmds[11] = "ifconig";
    ListOfOwnCmds[12] = "ping";
    ListOfOwnCmds[13] = "kill";

    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
        case 1:
            printf("\nGoodbye\n");
            exit(0);
        case 2:
            chdir(parsed[1]);
            return 1;
        case 3:
            openHelp();
            return 1;
        case 4:
            username = getenv("USER");
            printf("\nHello %s.\nMind that this is "
                   "not a place to play around."
                   "\nUse help to know more..\n",
                   username);
            return 1;
        default:
            break;
    }

    return 0;
}


// function for parsing command words 
void parseSpace(char* str, char** parsed)
{
    int i;

    for (i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int processString(char* str, char** parsed)
{
    parseSpace(str, parsed);

    if (ownCmdHandler(parsed))
        return 0;
    else
        return 1 ;
}

int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    init_shell();

    while (1) {
        // print shell line 
        printDir();
        // take input
        if (takeInput(inputString))
            continue;
        // process 
        processString(inputString,parsedArgs);
    }


    return 0;
} 
