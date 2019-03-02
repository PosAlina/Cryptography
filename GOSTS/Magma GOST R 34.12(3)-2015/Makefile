CC=g++
CFLAGS=-Wall -Werror -O2

all: gost

gost: main.o flags.o actions.o functions.o ecb.o ctr.o ofb.o cbc.o cfb.o mac.o magma.o
	$(CC) -o gost main.o flags.o actions.o functions.o ecb.o ctr.o ofb.o cbc.o cfb.o mac.o magma.o $(CFLAGS)

main.o: main.cpp flags.h actions.h
	$(CC) -c main.cpp $(CFLAGS)

flags.o: flags.cpp consts.h
	$(CC) -c flags.cpp $(CFLAGS)

actions.o: actions.cpp functions.h consts.h ecb.h ctr.h ofb.h cbc.h cfb.h mac.h
	$(CC) -c actions.cpp $(CFLAGS)

functions.o: functions.cpp consts.h
	$(CC) -c functions.cpp $(CFLAGS)

ecb.o: ecb.cpp consts.h functions.h magma.h
	$(CC) -c ecb.cpp $(CFLAGS)

ctr.o: ctr.cpp consts.h functions.h magma.h
	$(CC) -c ctr.cpp $(CFLAGS)

ofb.o: ofb.cpp consts.h functions.h magma.h
	$(CC) -c ofb.cpp $(CFLAGS)

cbc.o: cbc.cpp consts.h functions.h magma.h
	$(CC) -c cbc.cpp $(CFLAGS)

cfb.o: cfb.cpp consts.h functions.h magma.h
	$(CC) -c cfb.cpp $(CFLAGS)

mac.o: mac.cpp consts.h functions.h magma.h
	$(CC) -c mac.cpp $(CFLAGS)

magma.o: magma.cpp consts.h functions.h magma_consts.h
	$(CC) -c magma.cpp $(CFLAGS)

clean:
	rm  -rf *.o gost
