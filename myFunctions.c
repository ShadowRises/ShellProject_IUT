#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

#include "ligne_commande.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void command(char** line) {
    int pid, testCommand, returnCommand, index = -1, i = 0, fdRedirect;
    char* export;

    if (strcmp(line[0], "export") != 0){
        while(line[i] != NULL) {
            if(strcmp(line[i], ">") == 0 || strcmp(line[i], ">>") == 0
                    || strcmp(line[i], "2>") == 0 || strcmp(line[i], "2>>") == 0
                    || strcmp(line[i], "<") == 0) {
                index = i;
                break;
            }
            i++;
        }

        pid = fork();
        if(pid == 0) {

            if(index != -1) {

                if(strcmp(line[index], ">") == 0) {
                    fdRedirect = open(line[index + 1], O_WRONLY | O_CREAT, 0644);
                    dup2(fdRedirect, 1);
                } else if(strcmp(line[index], ">>") == 0) {
                    fdRedirect = open(line[index + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
                    dup2(fdRedirect, 1);
                } else if(strcmp(line[index], "2>") == 0) {
                    fdRedirect = open(line[index + 1], O_WRONLY | O_CREAT, 0644);
                    dup2(fdRedirect, 2);
                } else if(strcmp(line[index], "2>>") == 0) {
                    fdRedirect = open(line[index + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
                    dup2(fdRedirect, 2);
                }


                line[index] = NULL;
                execvp(line[0], line);
                close(fdRedirect);
                WEXITSTATUS(returnCommand);
            } else {
                testCommand = execvp(line[0], line);
                if(testCommand == -1) {
                    perror("Error ");
                    exit(-1);
                } else {
                    WEXITSTATUS(returnCommand);
                }
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
