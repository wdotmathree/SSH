#include "includes.h"
#include "network.h"
#include "random.h"
#include <openssl/evp.h>

// Send a kexinit packet
int kexinit(int s);
