CC = gcc
INC = ../../../../include
SRC = ../../../../src
LIBS = -lpthread
CFLAGS = -O2 -Wall -I$(INC) -I .

all: recipe

recipe: recipe.c
	$(CC) $(CFLAGS) recipe.c $(SRC)/csapp.o $(LIBS) -o recipe

clean:
	rm -f recipe *~
