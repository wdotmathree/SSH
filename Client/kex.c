#include "kex.h"

int kexinit(int s, EVP_MD_CTX *hctx)
{
  int e;
  // char tmp[] = "\x00\x00\x00\x12\x65\x63\x64h-sha2-nistp256\x00\x00\x00\x0bssh-ed25519\x00\x00\x00\x16\x61\x65s256-gcm@openssh.com\x00\x00\x00\x16\x61\x65s256-gcm@openssh.com\x00\x00\x00\x1dhmac-sha2-512-etc@openssh.com\x00\x00\x00\x1dhmac-sha2-512-etc@openssh.com\x00\x00\x00\x10zlib@openssh.com\x00\x00\x00\x10zlib@openssh.com\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
  char tmp[] = "\x00\x00\x00\x12\x65\x63\x64h-sha2-nistp256\x00\x00\x00\x0bssh-ed25519\x00\x00\x00\x16\x61\x65s256-gcm@openssh.com\x00\x00\x00\x16\x61\x65s256-gcm@openssh.com\x00\x00\x00\x1dhmac-sha2-512-etc@openssh.com\x00\x00\x00\x1dhmac-sha2-512-etc@openssh.com\x00\x00\x00\x04none\x00\x00\x00\x04none\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
  int tmplen = 184;
  char *payload = malloc(16 + tmplen);
  rand_bytes(payload, 16);
  memcpy(payload + 16, tmp, tmplen);
  if ((e = EVP_DigestUpdate(hctx, payload, tmplen + 16)) != 1)
    error("EVP_DigestUpdate", e);
  return send_ssh(s, payload, tmplen + 16, 20);
}
