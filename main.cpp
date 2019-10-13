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

#include "./simple/Simple.h"
#include "./admin/Admin.h"
#include "./sys/ping.h"
#include "./sys/ifconfig.h"
#include "./sys/kill.h"



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
int ownCmdHandler(char** parsed, int numOfArgs)
{
    int NoOfOwnCmds = 15, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    //simple
    ListOfOwnCmds[4] = "wc";
    ListOfOwnCmds[5] = "cat";
    ListOfOwnCmds[6] = "ls";
    ListOfOwnCmds[7] = "mv";
    ListOfOwnCmds[8] = "tail";
    //admin
    ListOfOwnCmds[9] = "chmod";
    ListOfOwnCmds[10] = "chown";
    ListOfOwnCmds[11] = "adduser";
    //sys
    ListOfOwnCmds[12] = "ifconig";
    ListOfOwnCmds[13] = "ping";
    ListOfOwnCmds[14] = "kill";

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
        case 5:
            wc(numOfArgs ,parsed);
            return 1;
        case 6:
            cat(numOfArgs ,parsed);
            return 1;
        case 7:
            ls();
            return 1;
        case 8:
            mv(numOfArgs ,parsed);
            return 1;
        case 9:
            tail(numOfArgs ,parsed);
            return 1;
        case 10:
            chmod(numOfArgs ,parsed);
            return 1;
        case 11:
            myChown(numOfArgs ,parsed);
            return 1;
        case 12:
            adduser(numOfArgs ,parsed);
            return 1;
        case 13:
            ifconfig(numOfArgs ,parsed);
            return 1;
        case 14:
            ping(numOfArgs ,parsed);
            return 1;
        case 15:
            myKill(numOfArgs ,parsed);
            return 1;



        default:
            break;
    }

    return 0;
}


// function for parsing command words 
void parseSpace(char* str, char** parsed, int* numOfArgs)
{
    int i;

    for (i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }

    *numOfArgs = i;
}

int processString(char* str, char** parsed)
{
    int numOfArgs = 0;
    parseSpace(str, parsed, &numOfArgs);

    if (ownCmdHandler(parsed, numOfArgs))
        return 0;
    else
        return 1 ;
}

int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
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
