#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

#include "ligne_commande.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int command(char** line) {
    int pid, testCommand, returnCommand;

    pid = fork();
    if(pid == 0) {
        testCommand = execvp(line[0], line);
        if(testCommand < 0) {
            perror("Unknow command ");
            exit(-1);
        } else {
            WEXITSTATUS(returnCommand);
        }
    } else {
        wait(&returnCommand);
    }
    
    return returnCommand;
}

#endif