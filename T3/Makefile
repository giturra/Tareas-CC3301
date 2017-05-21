CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lpthread

all: test-silla

test-silla: silla.o test-silla.o

silla.o test-silla.o: silla.h

clean:
	rm -f *.o
	rm -f test-silla
