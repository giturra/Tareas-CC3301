#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "concat.h"

static void check_bits(char *test, char *bits, char *ref) {
  if (strcmp(bits, ref)!=0) {
    fprintf(stderr, "El resultado de %s debio ser %s, no %s\n",
            test, ref, bits);
    exit(1);
  }
  free(bits);
}

static void check_uint(char *bits) {
  uint x= bits2uint(bits);
  char *inv= uint2bits(x);
  while (bits[1]!=0 && *bits=='0')
    bits++;
  if (strcmp(bits, inv)!=0) {
    fprintf(stderr, "El resultado de uint2bits(\"%s\") debio ser %s, no %s\n",
            bits, bits, inv);
    exit(1);
  }
  free(inv);
}

static void check_concat(char *s, char *r) {
  uint x= bits2uint(s);
  int n= strlen(s);
  uint y= bits2uint(r);
  int m= strlen(r);
  uint z= concat_bits(x, n, y, m);
  char u[n+m+1];
  strcpy(u, s);
  strcat(u, r);
  uint ref= bits2uint(u);
  if (ref!=z) {
    fprintf(stderr, "El resultado de concat_bits(0b%s,0b%s) debio ser 0b%s, "
            "no 0b%s", s, r, u, uint2bits(z));
    exit(1);
  }
}


int main() {
  // Chequea uint2bits
  check_bits("uint2bits(0)", uint2bits(0), "0");
  check_bits("uint2bits(1)", uint2bits(1), "1");
  check_bits("uint2bits(0xf)", uint2bits(0xf), "1111");
  check_bits("uint2bits(0x2d)", uint2bits(0x2d), "101101");
  check_bits("uint2bits(0x13b)", uint2bits(0x13b), "100111011");
  check_bits("uint2bits(0xf2d)", uint2bits(0xf2d), "111100101101");
  check_bits("uint2bits(0x3bc)", uint2bits(0x3bc), "1110111100");
  check_bits("uint2bits(0x5b1c)", uint2bits(0x5b1c), "101101100011100");

  // Chequea bits2uint
  check_uint("0");
  check_uint("1");
  check_uint("1111");
  check_uint("101101");
  check_uint("100111011");
  check_uint("111100101101");
  check_uint("1110111010");
  check_uint("101101100011010");
  check_uint("0000000");
  check_uint("0000101101100011010");

  // Chequea concat_bits
  check_concat("1111", "00101101");
  check_concat("100111100", "0101101100011010");
  printf("Felicitaciones!  Concat_bits funciona correctamente.\n");
  return 0;
}

