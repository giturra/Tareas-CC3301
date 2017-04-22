# Instrucciones
# =============
#
# Cree el archivo concat.c y programe ahi las funciones bits2int, uint2bits
# y concat_bits.  No modifique los demas archivos.
#
# Su tarea ya esta compilada con la opcion -g, que es necesaria para
# que use gdb y ddd para depurar los errores de programacion.
#
# Para compilar ingrese el comando:
#
# $ make
#
# Resuelva todos errores y warnings de la compilacion. 
# Cuando la compilacion sea exitosa, ejecute el programa de prueba con:
#
# $ ./test-concat
#
# El programa de prueba le indicara cual test falla o lo felicitara si
# paso todos los tests.
#
# Para borrar todos los archivos generados (incluyendo binarios):
# $ make clean

CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g

all: test-concat

test-concat: test-concat.o concat.o
test-concat.o concat.o: concat.h

clean:
	rm -f *.o
	rm -f test-concat
