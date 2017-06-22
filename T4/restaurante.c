#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "jsocket.h"
#include "util.h"

typedef void *(*Thread_fun)(void *);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int sillas[5] = {0, 0, 0, 0, 0};

int ubicarSilla();

int ubicarSilla() {
	for (int i = 0; i < 5; ++i) {
		if (sillas[i] == 0 && sillas[(i+1)%5] == 0 ) {
			return i;
		}
	}
	return -1;
}

int buscarSilla() {
	pthread_mutex_lock(&mutex);
	int ubicacion;
	while ((ubicacion  = ubicarSilla()) == -1) {
		pthread_cond_wait(&cond, &mutex);
	}
	sillas[(ubicacion+1)%5] = sillas[ubicacion] = 1;
	pthread_mutex_unlock(&mutex);
	return ubicacion;
}

void desocuparSilla(int k) {
	pthread_mutex_lock(&mutex);
	sillas[(k+1)%5] = sillas[k] = 0;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}

void *serv(long s) {
	char nombre[100];
	char len;
	int silla;
	char *fin;
	read(s, &len, 1);
	leer(s, nombre, len);
	printf("llega %s\n", nombre);
	silla = buscarSilla();
	write(s, &silla, sizeof(int));
	printf("%s a silla %d\n", nombre, silla);
	while ((strcmp((fin = getstr(s)),"fin")) != 0) {
		pthread_cond_wait(&cond, &mutex);
	}
	if (strcmp(fin, "fin") == 0) {
		desocuparSilla(silla);
		printf("%s libera %d\n", nombre, silla);
	}
	return NULL;
}

int main(int argc, char **argv) {
	long s, s2;
	int puerto;
	pthread_t pid;
	if (argc < 2) {
		printf("Usage: %s <puerto>\n", argv[0]);
		exit(1);
	}
	s = j_socket();
	puerto = atoi(argv[1]);
	if (j_bind(s, puerto) < 0) {
		fprintf(stderr, "bind failed\n");
		exit(1);
	}
	for(;;) {
		pthread_attr_t attr;
		s2 = j_accept(s);
		pthread_attr_init(&attr);
		if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) { //No espera join
      		fprintf(stderr, "No se puede establecer el atributo\n");
    	}
    	if (pthread_create(&pid, &attr, (Thread_fun)serv, (void *)s2) != 0) {
      		fprintf(stderr, "No pude crear thread para nuevo cliente %ld!!!\n", s2);
      		close(s2);
    	}
    	pthread_attr_destroy(&attr);

	}
	return 0;

}