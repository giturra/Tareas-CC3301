#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

void error(char *fmt, ...) { 
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);

  exit(1);
} 

int leer(int fd, char *buf, int n) {
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

void sendstr(int s, char *str) {
  char len= strlen(str)+1;
  if (write(s, &len, 1)!=1)
    error("sendstr: error al escribir en el socket\n");
  if (write(s, str, len)!=len)
    error("sendstr: error al escribir en el socket\n");
}

char *getstr(int s) {
  char len;
  char *str;
  if (read(s, &len, 1)!=1)
    error("getstr: error al leer del socket\n");
  str= (char*)malloc(len);
  if (leer(s, str, len)!=0)
    error("getstr: error al leer del socket\n");
  return str;
}

void fsendstr(FILE *sf, char *str) {
  char len= strlen(str)+1;
  int rc= fwrite(&len, 1, 1, sf);
  if (rc!=1)
    error("fsendstr: error al escribir en el socket (%d)\n", rc);
  rc= fwrite(str, len, 1, sf);
  if (rc!=1)
    error("fsendstr: error al escribir en el socket (%d)\n", rc);
}

char *fgetstr(FILE *sf) {
  char len;
  char *str;
  if (fread(&len, 1, 1, sf)!=1)
    error("fgetstr: error al leer del socket\n");
  str= (char*)malloc(len);
  if (fread(str, len, 1, sf)!=1)
    error("getstr: error al leer del socket\n");
  return str;
}

