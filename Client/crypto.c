#include "crypto.h"

char *keyctos;
char *keyctos;
char *ivctos;
char *ivctos;
char *hmacctos;
char *hmacctos;

EVP_PKEY *gen_pubkey()
{
  int e;
  EVP_PKEY_CTX *pctx, *kctx;
  EVP_PKEY *key = NULL, *params = NULL;
  if ((pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL)) == NULL)
    error("EVP_PKEY_CTX_new_id", 0);
  if (EVP_PKEY_paramgen_init(pctx) == NULL)
    error("EVP_PKEY_paramgen_init", 0);
  if (EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, NID_ED25519) == NULL)
    error("EVP_PKEY_CTX_set_ec_paramgen_curve_nid", 0);
  if (EVP_PKEY_paramgen(pctx, &params) == NULL)
    error("EVP_PKEY_paramgen", 0);
  if ((kctx = EVP_PKEY_CTX_new(params, NULL)) == NULL)
    error("EVP_PKEY_CTX_new", 0);
  if (EVP_PKEY_keygen_init(kctx) == NULL)
    error("EVP_PKEY_keygen_init", 0);
  if (EVP_PKEY_keygen(kctx, &key) == NULL)
    error("EVP_PKEY_keygen", 0);
  return key;
}
