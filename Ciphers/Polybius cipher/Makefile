CC=g++
CFLAGS=-Wall -Werror -O2

all: polybius_cipher

polybius_cipher: main.o polybius_functions.o polybius_encrypt.o polybius_decrypt.o
	$(CC) -o polybius main.o polybius_functions.o polybius_encrypt.o polybius_decrypt.o $(CFLAGS)

main.o: main.cpp globals.h polybius_functions.h
	$(CC) -c main.cpp $(CFLAGS)

polybius_functions.o: polybius_functions.cpp globals.h polybius_encrypt.h polybius_decrypt.h
	$(CC) -c polybius_functions.cpp $(CFLAGS)

polybius_encrypt.o: polybius_encrypt.cpp polybius_functions.h
	$(CC) -c polybius_encrypt.cpp $(CFLAGS)

polybius_decrypt.o: polybius_decrypt.cpp polybius_functions.h
	$(CC) -c polybius_decrypt.cpp $(CFLAGS)

clean:
	rm  -rf *.o polybius_cipher
