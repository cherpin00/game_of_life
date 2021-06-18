CC = gcc

all: main.o cells.o
	$(CC) main.o cells.o -o main

main.o: main.c
	$(CC) -c main.c

cells.o: cells.c cells.h
	$(CC) -c cells.c

run:
	./main input.txt

clean:
	rm *.o
	rm main