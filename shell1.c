#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ligne_commande.h"


int main(int argc, char* argv[]) {
    char **buffer;
    int test = 0;
    char* path;

    printf("Welcome to the Shell1, the alternative shell !\n\n");

    do {
        path = getenv("INVITE");

        if (path != NULL) {
            printf("%s ~> ", getenv("INVITE"));
        } else {
            printf("%s ~> ", getenv("PWD"));
        }
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
            command(buffer);
        }
        
    } while(test == 0);

    return 0;
}
