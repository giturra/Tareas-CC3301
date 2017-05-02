typedef double (*Funcion)(void *ptr, double x);
double raiz(Funcion f, void *ptr, double x0, double x1, double eps);
double raiz_poli(double a[], int n, double x0, double x1, double eps);

