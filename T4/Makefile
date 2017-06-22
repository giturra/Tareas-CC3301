CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g -pthread

all: filosofo restaurante

filosofo.o restaurante.o util.o: util.h
filosofo.o restaurante.o libjsocket.o: jsocket.h
filosofo: filosofo.o util.o libjsocket.o
restaurante: restaurante.o util.o libjsocket.o

clean:
	rm -f *.o
	rm -f filosofo restaurante
