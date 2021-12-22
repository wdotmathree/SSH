#include "includes.h"
#include "random.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

// Using at least 4 bytes, pad to a multiple of 16 bytes
unsigned char _pad(char *data, char **result, int len);
// Unpad an SSH packet
int _unpad(char *padded, char *data, int len, unsigned char padlen);
// Send an SSH packet
int send_ssh(int s, char *data, int len, unsigned char msg);
// Decode an SSH packet
int recv_ssh(int s, char *result);
// Connect to an SSH server
int create(char *host);
