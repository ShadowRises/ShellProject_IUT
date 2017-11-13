#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ligne_commande.h"


int main(int argc, char* argv[]) {
    char **buffer;
    int test = 0;
    int testCommand = 0;
    int pid;
    int returnCommand;

    printf("Welcome to the Shell1, the alternative shell !\n\n");

    do {
        pid = fork();
        if(pid == 0) {
            testCommand = execl("/bin/pwd", "pwd", NULL);
            if(testCommand == -1) {
                perror("Error with pwd ");
                exit(-1);
            } else {
                WEXITSTATUS(returnCommand);
            }
        } else {
            wait(&returnCommand);
        }

        if(returnCommand > 0) {
            exit(-1);
        }
        
        printf("~> ");
        fflush(stdout);
        buffer = lis_ligne();

        // Tests of verification of the buffer
        if(fin_de_fichier(buffer)) {
            test = 1;
            printf("\n");
        }

        else if(ligne_vide(buffer))
            buffer[0] = "\0";

        else if(strcmp(buffer[0], "exit") == 0)
            test = 1;

        else {

            // Test if it's an existing command
            command(buffer);
        }
        
    } while(test == 0);

    return 0;
}