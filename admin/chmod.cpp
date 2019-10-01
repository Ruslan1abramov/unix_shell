//
// Created by rusla on 10/1/2019.
//

#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    string str;

    if (argc != 3) {
        printf("Usage: %s [permission oct representation] [ file dir ] \n", argv[0]);
        exit(1);
    }

    if (strlen(argv[1]) != 3) {
        printf("Please set a 3 number permission representation\n");
        exit(1);
    }
    str = argv[1];
    for(char& c : str) {
        if (7 - c < 0 || 7 - c > 7){
            printf("Please set a value between 0 to 7\n");
            exit(1);
        }
    }

    str.insert(0, "0");
    chmod(argv[2], str);

}
