#include "crypto.h"

char *keyctos;
char *keyctos;
char *ivctos;
char *ivctos;
char *hmacctos;
char *hmacctos;

EC_KEY *gen_pubkey()
{
  int e;
  EC_KEY *ec_key = EC_KEY_new();
  if (ec_key == NULL)
    error("EC_KEY_new", 0);
  EC_GROUP *ec_group = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
  if (ec_group == NULL)
    error("EC_GROUP_new_by_curve_name", 0);
  if ((e = EC_KEY_set_group(ec_key, ec_group)) != 1)
    error("EC_KEY_set_group", e);
  if ((e = EC_KEY_generate_key(ec_key)) != 1)
    error("EC_KEY_generate_key", e);
  return ec_key;
}
