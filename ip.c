#include <stdio.h>
#include <netinet/if_ether.h>
#include "ip.h"
#include "color.h"

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

struct my_ip_header* ip_header(const u_char* packet) {
  struct my_ip_header *hdr;
  hdr = (struct my_ip_header *) packet;

  char source[16];
  char dest[16];
  ip_address(hdr->source_ip, source);
  ip_address(hdr->dest_ip, dest);

  printf("\tIP header - IPv%d", IP_VERSION(hdr));
  printf(" source: " BLUE("%s") " destination: " BLUE("%s"), source, dest);
  printf(" ttl: " BLUE("%d\n"), hdr->ttl);

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

