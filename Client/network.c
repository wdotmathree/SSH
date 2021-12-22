#include "network.h"

unsigned char _pad(char *data, char **result, int len)
{
  unsigned char padlen = 20 - ((len + 4) % 16);
  *result = malloc(len + padlen);
  memcpy(*result, data, len);
  rand_bytes(*result + len, padlen);
  return padlen;
}

int _unpad(char *padded, char *data, int len, unsigned char padlen)
{
  memcpy(data, padded, len - padlen);
  return len - padlen;
}

int send_ssh(int s, char *data, int len, unsigned char msg)
{
  char *packet = malloc(len + 6);
  memcpy(packet + 6, data, len);
  packet[5] = msg;
  char *padded;
  unsigned char padding_length = _pad(packet, &padded, len + 6);
  free(packet);
  padded[4] = padding_length;
  uint32_t packet_length = htonl(len + 2 + padding_length);
  memcpy(padded, &packet_length, 4);
  int res = send(s, padded, ntohl(packet_length) + 4, 0);
  free(padded);
  return res;
}

int recv_ssh(int s, char *buf)
{
  int len = recv(s, buf, 35000, 0);
  if (len == 0)
    return 0;
  uint32_t packet_length = ntohl(*(uint32_t *)buf);
  unsigned char padding_length = buf[4];
  int resultlen = _unpad(buf + 5, buf, packet_length - 1, padding_length);
  return resultlen;
}

int create(char *host)
{
  int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(22);
  inet_pton(AF_INET, host, &addr.sin_addr.s_addr);
  connect(s, (const struct sockaddr *)&addr, sizeof addr);
  return s;
}
