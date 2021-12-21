#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *function, int r)
{
  printf("Function: %s returned value: %i", function, r);
  exit(r);
}
