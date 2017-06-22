#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "jsocket.h"
#include "util.h"

int main(int argc, char **argv) {
	long s;
	char *nombre;
	char host[100];
	int silla;
	char fin[4];
	fin[3] = 0;
	char *str = getenv("REST");
	char *puertoS = strchr(str, ':');

	puertoS++;
	int puerto = atoi(puertoS);
	for(int i = 0; str[i] != ':'; ++i) {
		host[i] = str[i];
		if (str[i+1] == ':') {
			host[i+1] = '\0';
		}
	}
	if (argc < 2) {
		printf("Usage: %s <nombre>\n", argv[0]);
		exit(1);
	}
	s = j_socket();
	nombre = argv[1];
	if (j_connect(s, host, puerto) < 0) {
		fprintf(stderr, "connection refused\n");
    	exit(1);
	}
	int len = strlen(nombre)+1;
	write(s, &len, 1);
	write(s, nombre, len);
	read(s, &silla, sizeof(int));
	printf("%d\n", silla);
	scanf("%s",fin);
	//printf("%s y su largo es %lu\n", fin, strlen(fin));
	if (strlen(fin) != 3) {
		fprintf(stderr, "Si termino de comer debe ingresar fin\n");
    	exit(1);	
    } else {
    	//printf("%s\n", "hello");
    	sendstr(s, fin);
    }
	return 0;
}