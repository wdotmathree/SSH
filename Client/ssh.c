#include "includes.h"
#include "network.h"
#include "kex.h"

#define VERSION_STRING "SSH-2.0-SSSH_0.0.1 SSSH\r\n"

int main()
{
  char *buf = malloc(35000);
  int e;
  int len;
  EVP_MD_CTX *hctx;
  if ((hctx = EVP_MD_CTX_new()) == NULL)
    error("EVP_MD_CTX_new", 0);
  if ((e = EVP_DigestInit_ex(hctx, EVP_sha256(), NULL)) != 1)
    error("EVP_DigestInit_ex", e);
  int s = create("localhost");
  send(s, VERSION_STRING, 25, 0);
  if ((e = EVP_DigestUpdate(hctx, VERSION_STRING, 25)) != 1)
    error("EVP_DigestUpdate", e);
  len = recv(s, buf, 35000, 0);
  if ((e = EVP_DigestUpdate(hctx, buf, len)) != 1)
    error("EVP_DigestUpdate", e);
  kexinit(s);
  len = recv_ssh(s, &buf);
  shutdown(s, SHUT_WR);
  recv(s, buf, 35000, 0);
  shutdown(s, SHUT_RD);
  close(s);
  return 0;
}
