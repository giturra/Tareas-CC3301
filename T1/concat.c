#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concat.h"

uint bitMostSignificant(uint x);

uint bits2uint(char *s) {
  char bitString[] = {'0','0', '0', '0', '0','0', '0', '0','0','0', '0', '0','0','0', '0', '0',
  '0','0', '0', '0','0','0', '0', '0','0','0', '0', '0','0','0', '0', '0',0};
  char *pointer1 = s + strlen(s) - 1;
  char *pointer2 = bitString + strlen(bitString) - 1;
  uint count1 = strlen(s);
  while(count1) {
    *pointer2 = *pointer1;
    pointer1--;
    pointer2--;
    count1--;
  }

  uint num = 0;
  int i = 0;
  char *pointer3 = bitString;
  for (; i < 32; ++i) {
    if (*pointer3 == '1') {
      num |= 1 << (31 - i);
    }
    pointer3++;
  }
  return num;
}

//uint2bits

char *uint2bits(uint x) {
  uint bits = bitMostSignificant(x);
  char *str = malloc(bits + 1);
  char *pointer = str + bits;
  *pointer = 0;
  pointer--;
  while(1) {
    
    *pointer = x & 1 ? '1' : '0';
    x >>= 1; 
    pointer--;
    bits--;
    if (bits+1 == 1) {
      break;
    } 
  }
  return str;
}

uint concat_bits(uint x, int n, uint y, int m) {
	uint z;
  x = x << (32 - n);
  x = x >> (32 - (n + m));
  z = x | y;
  return z;

}

uint bitMostSignificant(uint x) {
  uint mask = 1 << (sizeof(int) * 8 - 1);
  uint count = 0;
  while (mask) {
    if (x & mask) {
      return (32 - count);
    }
    count++;
    mask >>= 1;
  }
  return 1;
}


