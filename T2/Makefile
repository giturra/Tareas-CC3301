# Instrucciones
# =============
#
# Cree el archivo raiz.c y programe ahi las funciones raiz y raiz_poli. 
# No modifique los demas archivos.
#
# Su tarea sera compilada con la opcion -g, que es necesaria para
# que use gdb y ddd para depurar los errores de programacion.
#
# Para compilar ingrese el comando:
#
# $ make
#
# Resuelva todos los errores y warnings de la compilacion. 
# Cuando la compilacion sea exitosa, ejecute el programa de prueba con:
#
# $ ./test-raiz
#
# El programa de prueba le indicara cual test falla o lo felicitara si
# paso todos los tests.
#
# Para borrar todos los archivos generados (incluyendo binarios):
# $ make clean

CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lm

all: test-raiz

test-raiz: test-raiz.o raiz.o
test-raiz.o raiz.o: raiz.h

clean:
	rm -f *.o
	rm -f test-raiz
