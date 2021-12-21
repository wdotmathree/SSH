#include "kex.h"

int kexinit(int s)
{
  char tmp[] = "\x00\x00\x00\x11\x63urve25519-sha256\x00\x00\x00\x0bssh-ed25519\x00\x00\x00\x16\x61\x65s256-gcm@openssh.com\x00\x00\x00\x16\x61\x65s256-gcm@openssh.com\x00\x00\x00\x1dhmac-sha2-512-etc@openssh.com\x00\x00\x00\x1dhmac-sha2-512-etc@openssh.com\x00\x00\x00\x10zlib@openssh.com\x00\x00\x00\x10zlib@openssh.com\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
  int tmplen = 208;
  char *payload = malloc(17 + tmplen);
  rand_bytes(payload + 1, 16);
  memcpy(payload + 17, tmp, tmplen);
  payload[0] = '\x14';
  return send_ssh(s, payload, tmplen + 16);
}
