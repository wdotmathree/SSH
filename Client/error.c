#include "includes.h"

void error(char *function, int r)
{
  printf("Function: %s returned value: %i", function, r);
  exit(r);
}