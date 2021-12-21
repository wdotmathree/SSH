#include "random.h"

void rand_bytes(char *result, int num)
{
  FILE *f = fopen("/dev/urandom", "r");
  fread(result, num, 1, f);
  fclose(f);
}

int rand_int()
{
  int res;
  rand_bytes((char *)&res, sizeof(int));
  return res;
}
