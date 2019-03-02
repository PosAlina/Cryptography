CC=g++
CFLAGS=-Wall -Werror -O2

all: vigenere_cipher

vigenere_cipher: main.o vigenere_functions.o vigenere_encrypt.o vigenere_decrypt.o
	$(CC) -o vigenere main.o vigenere_functions.o vigenere_encrypt.o vigenere_decrypt.o $(CFLAGS)

main.o: main.cpp globals.h vigenere_functions.h vigenere_encrypt.h vigenere_decrypt.h
	$(CC) -c main.cpp $(CFLAGS)

vigenere_functions.o: vigenere_functions.cpp globals.h consts.h vigenere_encrypt.h vigenere_decrypt.h
	$(CC) -c vigenere_functions.cpp $(CFLAGS)

vigenere_encrypt.o: vigenere_encrypt.cpp vigenere_functions.h
	$(CC) -c vigenere_encrypt.cpp $(CFLAGS)

vigenere_decrypt.o: vigenere_decrypt.cpp vigenere_functions.h
	$(CC) -c vigenere_decrypt.cpp $(CFLAGS)

clean:
	rm  -rf *.o vigenere_cipher
