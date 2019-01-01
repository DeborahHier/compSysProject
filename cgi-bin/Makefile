CC = gcc
INC = ../../../../include
SRC = ../../../../src
LIB = -lpthread


CFLAGS = -O2 -Wall -I$(INC) -I ..

all: recipe

recipe: recipe.c
	$(CC) $(CFLAGS) recipe $(SRC)/csapp.o $(LIB) -o recipe.c

clean:
	rm -f recipe *~
