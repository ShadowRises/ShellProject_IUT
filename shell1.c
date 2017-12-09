#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ligne_commande.h"

int main(int argc, char* argv[]) {
    char **buffer;
    int processPid[SIZE_PROCESS] = {0};
    int returnWait, test = 0;
    char* path;

    printf("Welcome to the Shell1, the alternative shell !\n\n");

    do {
        for(int i = 0; i < SIZE_PROCESS; i++) {
            if(processPid[i] != 0) {
                returnWait = waitpid(processPid[i], NULL, WNOHANG);
                if(returnWait != 0) {
                    printf("%d finished\n\n", processPid[i]);
                    processPid[i] = 0;
                }
            }
        }

        path = getenv("INVITE");

        if (path != NULL) {
            printf("%s ~> ", getenv("INVITE"));
        } else {
            printf("%s ~> ", getenv("PWD"));
        }
        fflush(stdout);
        buffer = lis_ligne();

        for(int i = 0; i < SIZE_PROCESS; i++) {
            if(processPid[i] != 0) {
                returnWait = waitpid(processPid[i], NULL, WNOHANG);
                if(returnWait != 0) {
                    printf("%d finished\n\n", processPid[i]);
                    processPid[i] = 0;
                }
            }
        }

        // Tests of verification of the buffer
        if(fin_de_fichier(buffer)) {
            test = 1;
            printf("\n");
        }

        else if(ligne_vide(buffer))
            strcpy(buffer[0], "\0");

        else if(strcmp(buffer[0], "exit") == 0)
            test = 1;

        else {
            command(buffer, processPid);
        }

        for(int i = 0; i < SIZE_PROCESS; i++) {
            if(processPid[i] != 0) {
                returnWait = waitpid(processPid[i], NULL, WNOHANG);
                if(returnWait != 0) {
                    printf("%d finished\n\n", processPid[i]);
                    processPid[i] = 0;
                }
            }
        }

    } while(test == 0);

    return 0;
}
