#include "random.h"

// Gets num bytes of random data from /dev/urandom and stores it in result
void rand_bytes(char *result, int num)
{
  FILE *f = fopen("/dev/urandom", "r");
  fread(result, num, 1, f);
  fclose(f);
}

// Gets a random integer
int rand_int()
{
  int res;
  rand_bytes((char *)&res, sizeof(int));
  return res;
}
