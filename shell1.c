#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ligne_commande.h"

int main(int argc, char* argv[]) {
    char **buffer;
    int test = 0;
    int testPWD = 0;
    int pid;
    int retourPWD;

    printf("Welcome to the Shell1, the alternative shell !\n\n");

    do {
        pid = fork();
        if(pid == 0) {
            testPWD = execl("/bin/pwd", "pwd", "-P", NULL);
            if(testPWD == -1) {
                perror("Error with pwd ");
                exit(-1);
            } else {
                WEXITSTATUS(retourPWD);
            }
        } else {
            wait(&retourPWD);
        }

        if(retourPWD > 0) {
            exit(-1);
        }
        
        printf("~> ");
        fflush(stdout);
        buffer = lis_ligne();

        // Tests de vérication de la ligne entrée
        if(fin_de_fichier(buffer)) {
            test = 1;
            printf("\n");
        }
        else if(ligne_vide(buffer))
            buffer[0] = "\0";
        else if(!abs(strcmp(buffer[0], "exit")))
            test = 1;
        
    } while(test == 0);

    return 0;
}