#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raiz.h"

double expax(void *ptr, double x) {
 double *pa= ptr, a= *pa;
 return exp(a*x)-10; // calcula e elevado a a*x-10
}

int main() {
  // Test para raiz
  {
    double a= 3.;
    double y0= expax(&a, 0.);
    double y1= expax(&a, 1.);
    printf("%f %f\n", y0, y1);
    double cero= raiz(expax, &a, 0., 1., 0.00001);
    if (cero<0.767517 || cero>0.767532) {
      fprintf(stderr, "La raiz %f es incorrecta\n", cero);
      exit(1);
    }
    printf("La raiz %f es aproximadamente correcta\n", cero);
  }

  // Test para raiz_poli
  {
    double a[]= {40, 27, -12, 1};
    double cero1= raiz_poli(a, 3, 0, -3, 0.00001);
    if (cero1<-1.00001 || cero1>-0.99999) {
      fprintf(stderr, "La raiz %f es incorrecta\n", cero1);
      exit(1);
    }
    printf("La raiz %f es aproximadamente correcta\n", cero1);
    double cero2= raiz_poli(a, 3, 0, 7, 0.00001);
    if (cero2<4.99999 || cero2>5.00001) {
      fprintf(stderr, "La raiz %f es incorrecta\n", cero2);
      exit(1);
    }
    printf("La raiz %f es aproximadamente correcta\n", cero2);
    double cero3= raiz_poli(a, 3, 7, 15, 0.00001);
    if (cero3<7.99999 || cero3>8.00001) {
      fprintf(stderr, "La raiz %f es incorrecta\n", cero3);
      exit(1);
    }
    printf("La raiz %f es aproximadamente correcta\n", cero3);
  }

  printf("Felicitaciones, su tarea funciona adecuadamente\n");
  return 0;
}  
