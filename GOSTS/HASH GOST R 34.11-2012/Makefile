CC=g++
CFLAGS=-Wall -Werror -O2

all: gost

gost: main.o flags.o
	$(CC) -o gost main.o flags.o $(CFLAGS)

main.o: main.cpp flags.h hash_consts.h consts.h
	$(CC) -c main.cpp $(CFLAGS)

flags.o: flags.cpp consts.h
	$(CC) -c flags.cpp $(CFLAGS)

clean:
	rm  -rf *.o gost
