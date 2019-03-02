CC=g++
CFLAGS=-Wall -Werror -O2

all: g512sum g256sum

g512sum: main_512.o hash.o
	$(CC) -o g512sum main_512.o hash.o $(CFLAGS)

g256sum: main_256.o hash.o
	$(CC) -o g256sum main_256.o hash.o $(CFLAGS)

main_512.o: main_512.cpp global_consts.h hash.h
	$(CC) -c main_512.cpp $(CFLAGS)

main_256.o: main_256.cpp global_consts.h hash.h
	$(CC) -c main_256.cpp $(CFLAGS)

hash.o: hash.cpp hash.h global_consts.h hash_consts.h
	$(CC) -c hash.cpp $(CFLAGS)

clean:
	rm  -rf *.o g512sum g256sum
