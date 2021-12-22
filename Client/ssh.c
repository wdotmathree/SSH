#include "includes.h"
#include "network.h"
#include "crypto.h"
#include "kex.h"

#define VERSION_STRING "SSH-2.0-SSSH_0.0.1 SSSH\r\n"

int main()
{
  char *buf = malloc(35000);
  int e;
  size_t len;
  EVP_MD_CTX *hctx;
  if ((hctx = EVP_MD_CTX_new()) == NULL)
    error("EVP_MD_CTX_new", 0);
  if ((e = EVP_DigestInit_ex(hctx, EVP_sha256(), NULL)) != 1)
    error("EVP_DigestInit_ex", e);
  int s = create("localhost");
  send(s, VERSION_STRING, 25, 0);
  if ((e = EVP_DigestUpdate(hctx, VERSION_STRING, 23)) != 1)
    error("EVP_DigestUpdate", e);
  len = recv(s, buf, 35000, 0);
  if ((e = EVP_DigestUpdate(hctx, buf, len - 2)) != 1)
    error("EVP_DigestUpdate", e);
  kexinit(s, hctx);
  recv_ssh(s, buf);
  EC_KEY *key = gen_pubkey();
  BIGNUM *x = BN_new();
  BIGNUM *y = BN_new();
  EC_POINT_get_affine_coordinates(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), x, y, NULL);
  len = BN_bn2bin(x, (unsigned char *)buf + 5);
  len += BN_bn2bin(y, (unsigned char *)buf + len + 5);
  buf[4] = '\x04';
  len = htonl(len + 1);
  memcpy(buf, &len, 4);
  len = ntohl(len);
  BN_free(x);
  BN_free(y);
  send_ssh(s, buf, len + 4, 30);
  len = recv_ssh(s, buf);
  shutdown(s, SHUT_WR);
  recv(s, buf, 35000, 0);
  free(buf);
  shutdown(s, SHUT_RD);
  close(s);
  return 0;
}
