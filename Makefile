CC = gcc
CFLAGS = -O2 -Wall -I ..

PROGS = echoclient\
	recipe

all: adder

adder: adder.c
	$(CC) $(CFLAGS) -o adder adder.c

clean:
	rm -f adder *~
