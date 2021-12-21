#include "includes.h"
#include "network.h"
#include "kex.h"

#define VERSION_STRING "SSH-2.0-SSSH_0.0.1 SSSH\r\n"

int main()
{
  char *buf = malloc(35000);
  int s = create("localhost");
  send(s, VERSION_STRING, 25, 0);
  shutdown(s, SHUT_WR);
  recv(s, buf, 35000, 0);
  shutdown(s, SHUT_RD);
  close(s);
  return 0;
}
