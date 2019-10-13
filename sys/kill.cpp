//
// Created by rusla on 10/1/2019.
//
#include<stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<signal.h>

int myKill(int argc, char **argv)
{

    if (argc != 2) {
        printf("Usage: %s [process ID]  \n", argv[0]);
        return 1;
    }
    kill(atoi(argv[1]), SIGKILL);

}
