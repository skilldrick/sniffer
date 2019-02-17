#include <stdio.h>
#include <netinet/if_ether.h>
#include "ip.h"

void ip_address(u_char* bytes, char* addr) {
  sprintf(
    addr,
    "%d.%d.%d.%d",
    // this is janky - should convert between network and host byte order
    bytes[2],
    bytes[3],
    bytes[0],
    bytes[1]
  );
}

#define RED(str)     "\x1b[31m" str "\x1b[0m"
#define GREEN(str)   "\x1b[32m" str "\x1b[0m"
#define YELLOW(str)  "\x1b[33m" str "\x1b[0m"
#define BLUE(str)    "\x1b[34m" str "\x1b[0m"
#define MAGENTA(str) "\x1b[35m" str "\x1b[0m"
#define CYAN(str)    "\x1b[36m" str "\x1b[0m"

struct my_ip_header* ip_header(const u_char* packet) {
  struct my_ip_header *hdr;
  hdr = (struct my_ip_header *) packet;

  char source[16];
  char dest[16];
  ip_address(hdr->source_ip, source);
  ip_address(hdr->dest_ip, dest);
  char version = ((hdr->version_and_ihl) & 0xf0) >> 4;
  char header_length = hdr->version_and_ihl & 0x0f;

  printf("\tIP header - IPv%d ", version);
  printf("header length:" BLUE(" %d "), header_length);
  printf("length:" BLUE(" %d "), ntohs(hdr->length));
  printf("source:" BLUE(" %s ") "destination:" BLUE(" %s "), source, dest);
  printf("ttl:" BLUE(" %d ") "protocol:" BLUE(" %d \n"), hdr->ttl, hdr->protocol);

  //
  /*
  // print all the bytes
  printf("\t");
  for (int i = 0; i < 20; i++) {
    printf("%02x ", packet[i]);
  }
  printf("\n");
  */

  return hdr;
}

