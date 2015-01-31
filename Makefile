#flags
CC=g++
CFLAGS=-c -Wall -g

all: ConsoleApp

ConsoleApp: main.o
	$(CC) main.o -o ConsoleApp

main.o: main.cc
	$(CC) $(CFLAGS) main.cc -o main.o

clean:
	rm *.o