CC=gcc
CFLAGS=-Wall -Werror
BIN=shell1

all: $(BIN)

$(BIN): shell1.o myFunctions.o ligne_commande.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o $(BIN)
