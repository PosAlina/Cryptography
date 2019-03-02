CC=g++
CFLAGS=-Wall -Werror -O2

all: afine_cipher

afine_cipher: main.o afine_functions.o afine_encrypt.o afine_decrypt.o afine_break.o
	$(CC) -o afine main.o afine_functions.o afine_encrypt.o afine_decrypt.o afine_break.o $(CFLAGS)

main.o: main.cpp globals.h afine_functions.h afine_encrypt.h afine_decrypt.h afine_break.h
	$(CC) -c main.cpp $(CFLAGS)

afine_functions.o: afine_functions.cpp globals.h consts.h
	$(CC) -c afine_functions.cpp $(CFLAGS)

afine_encrypt.o: afine_encrypt.cpp afine_functions.h
	$(CC) -c afine_encrypt.cpp $(CFLAGS)

afine_decrypt.o: afine_decrypt.cpp afine_functions.h
	$(CC) -c afine_decrypt.cpp $(CFLAGS)

afine_break.o: afine_break.cpp afine_functions.h afine_decrypt.h globals.h
	$(CC) -c afine_break.cpp $(CFLAGS)

clean:
	rm  -rf *.o afine_cipher
