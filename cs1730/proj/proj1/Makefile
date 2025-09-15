CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

compile: proj1.out

proj1.out: proj1.o compress.o decompress.o
	$(CC) $(LFLAGS) -o proj1.out proj1.o compress.o decompress.o

proj1.o: proj1.c compress.h decompress.h
	$(CC) $(CFLAGS) proj1.c

compress.o: compress.c compress.h decompress.h
	$(CC) $(CFLAGS) compress.c

decompress.o: decompress.c compress.h decompress.h
	$(CC) $(CFLAGS) decompress.c

run: proj1.out
	./proj1.out -c ATTCGG
	./proj1.out -d 3 132

clean:
	rm *.o
	rm proj1.out
