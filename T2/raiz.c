#include <stdio.h>
#include <math.h>
#include "raiz.h"

typedef struct {
	int n;
	double *a;
}Polinomyal;

double evaluate_polinomyal(void *ptr, double x);

int samesing(double a, double b);

int samesing(double a, double b) {
	return a * b > 0;
}

double evaluate_polinomyal(void *ptr, double x) {
	Polinomyal *p = (Polinomyal*)ptr;
	int n = p->n;
	double *a = p->a;
	int limit = 0;
	double result = 0.0;
	for (; n >= limit; --n) {
		double val = a[n]*pow(x, n);
		result += val;
	
	}
	return result;
}

double raiz(Funcion f, void *ptr, double x0, double x1, double eps) {
	double xm = eps + 1;
	while (fabs(x0 - x1) >= eps) {
		xm = ((x0 + x1) / 2.0);
		double valFxm = f(ptr, xm);
		double valFx0 = f(ptr, x0);
		if (samesing(valFxm, valFx0)) {
			x0 = xm;
		} else {
			x1 = xm;
		}
	}
	return xm;

}

double raiz_poli(double a[], int n, double x0, double x1, double eps) {
	Polinomyal p;
	p.a = a;
	p.n = n;
	return raiz(evaluate_polinomyal, &p, x0, x1, eps);

}
