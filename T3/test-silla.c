#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include "silla.h"

// el atributo static hace que la funcion o variable global declarada
// sea conocida solo dentro de este archivo

static void comer(int micros);
static void pensar();

static int ocup[5];
static int tam= 5;

typedef struct {
  char *nom;
  int iter;
  int micros;
  int status;
} Param;

static void *filosofo(void *ptr) {
  Param *p= ptr;
  for (int i=0; i<p->iter; i++) {
    int k= buscarSilla();
    p->status= 1; // silla encontrada
    if (ocup[k] || ocup[(k+1)%tam]) {
      fprintf(stderr, "La silla %d estaba ocupada\n", k);
      exit(1);
    }
    ocup[k]= ocup[(k+1)%tam]= 1;

    if (p->nom!=NULL)
      printf("%s encontro silla %d\n", p->nom, k);
    comer(p->micros);

    ocup[k]= ocup[(k+1)%tam]= 0;
    desocuparSilla(k);
    pensar();
  }
  p->status= 2; // teminado
  return NULL;
}
 
static void comer(int micros) {
  if (micros>0)
    usleep(micros);
}

static void pensar() {
}

static long long getMicros() {
  struct timeval tvi;
  gettimeofday(&tvi, NULL);
  return tvi.tv_sec*1000000+tvi.tv_usec;
}

static void testRobustez(int n, int mul) {
  long long ini= getMicros(); // tiempo de inicio
  pthread_t f[n];
  Param p[n];
  for (int k= 0; k<n; k++) {
    p[k].nom= NULL;
    p[k].iter= (k+1)*mul;
    p[k].micros= 0;
    p[k].status= 0;
    pthread_create(&f[k], NULL, filosofo, &p[k]);
  }

  for (int k= 0; k<n; k++)
    pthread_join(f[k], NULL);
  long long fin= getMicros(); // tiempo final
  printf("Tiempo transcurrido: %lld microsegundos\n", fin-ini);
}

int main() {
  printf("Test de funcionalidad\n");
  printf("---------------------\n");
  long long ini= getMicros(); // tiempo de inicio
  pthread_t f0, f1, f2;       // los 3 filosofos
  // se crea un filosofo que come una sola vez durante un segundo
  Param p0= {"primer filosofo", 1, 1000000, 0};
  pthread_create(&f0, NULL, filosofo, &p0); // debe encontrar silla

  // se crea otro filosofo que come una sola vez durante un segundo
  Param p1= {"segundo filosofo", 1, 1000000, 0}; 
  pthread_create(&f1, NULL, filosofo, &p1);

  usleep(300000); // esperamos 0.3 segundos
  // se crea un tercer filosofo que no debe encontrar silla de inmediato
  Param p2= {"tercer filosofo", 1, 1000000, 0};
  pthread_create(&f2, NULL, filosofo, &p2);

  usleep(300000); // esperamos otros 0.3 segundos
  if (p2.status!=0) {
    fprintf(stderr, "El tercer filosofo no debio encontrar silla\n");
    exit(1);
  }

  // despues de un segundo del inicio los 2 primeros filosofos terminan
  pthread_join(f0, NULL);
  pthread_join(f1, NULL);
  long long med= getMicros(); // tiempo transcurrido desde el inicio
  printf("Primeros 2 threads terminaron en %lld microsegundos\n", med-ini);
  usleep(500000);
  if (p2.status!=1) {
    fprintf(stderr, "El tercer filosofo debe estar comiendo, no terminado\n");
    exit(1);
  }
  pthread_join(f2, NULL);
  long long fin= getMicros();
  long long delta= fin-ini; // tiempo transcurrido desde el inicio
  if (delta>2100000) { // No debe exceder 2.1 segundos
    fprintf(stderr, "%lld microsegundos es demasiado para este test\n", delta);
    exit(1);
  }
  printf("Primer test tomo %lld microsegundos.  Aprobado.\n\n", delta);

  printf("Test de robustez con 5 filosofos: debe pasar en anakena\n");
  printf("-------------------------------------------------------\n");
  printf("Buscando dataraces.  Tomo unos 25 segundos en mi PC\n");
  testRobustez(5, 5000000);
  printf("Test de robustez con 5 filosofos aprobado\n\n");

  printf("Test de robustez con 50 filosofos: puede fallar en anakena\n");
  printf("----------------------------------------------------------\n");
  printf("Buscando dataraces.  Tomo unos 30 segundos en mi PC\n");
  testRobustez(50, 100000);
  printf("Test de robustez con 50 filosofos aprobado\n\n");

  printf("Felicitaciones: su tarea paso todos los tests.\n");
  return 0;
}

