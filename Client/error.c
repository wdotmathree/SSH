#include "includes.h"

void error(char *function, int r)
{
  printf("Function: %s returned value: %i\n", function, r);
  printf("%s\n", ERR_error_string(ERR_get_error(), NULL));
  exit(r);
}