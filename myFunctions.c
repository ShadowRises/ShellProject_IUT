#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

#include "ligne_commande.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int command(char** line) {
    int pid, testCommand, returnCommand;
    char* export;

    if (strcmp(line[0], "export") != 0){
        pid = fork();
        if(pid == 0) {
            testCommand = execvp(line[0], line);
            if(testCommand == -1) {
                perror("Error ");
                exit(-1);
            } else {
                WEXITSTATUS(returnCommand);
            }
        } else {
            wait(&returnCommand);
        }
    } else if (strcmp(line[0], "export") == 0) {
        export = separe_egal(line[1]);

        if(getenv(line[1]) != NULL) {
            if (setenv(line[1], export, 1) < 0) {
                perror("Erreur lors de l'ajout de la variable d'environnement ");
                exit(-1);
            }
        } else {
            if (setenv(line[1], export, 0) < 0) {
                perror("Erreur lors de l'ajout de la variable d'environnement ");
                exit(-1);
            }
        }        
    }
}

#endif