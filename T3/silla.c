#include <stdio.h>
#include <pthread.h>
#include "silla.h"

pthread_mutex_t mutex;
pthread_cond_t cond;
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
	int ubicacion = ubicarSilla();
	while (ubicacion == -1) {
		printf("%s\n", "espero");
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