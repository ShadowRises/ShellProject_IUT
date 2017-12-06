main: shell1.o myFunctions.o ligne_commande.o
	gcc -o ./bin/shell1 shell1.o myFunctions.o ligne_commande.o

shell1.o: shell1.c ligne_commande.h ligne_commande.c
	gcc -c -Wall shell1.c

myFunctions.o: ligne_commande.h
	gcc -c -Wall myFunctions.c

ligne_commande.o: ligne_commande.h ligne_commande.c
	gcc -c -Wall ligne_commande.c
