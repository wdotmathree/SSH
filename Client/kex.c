#include "kex.h"

int kexinit(int s)
{
  char *payload = malloc(16);
  rand_bytes(*payload, 16);
  int len = 16;
  char tmp[] = "curve25519-sha256";
  int tmplen = htonl(strlen(tmp));
  memcpy(payload + len, (char *)&tmplen, 4);
  len += 4;
  strcpy(payload + len, tmp);
}
