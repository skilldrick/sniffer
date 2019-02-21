#include <netinet/if_ether.h>
#include <stdio.h>
#include "udp.h"
#include "color.h"

void udp_header(const unsigned char* packet) {
  struct my_udp_header* hdr;
  hdr = (struct my_udp_header *) packet;
  printf("\t\tUDP - Source port: " BLUE("%d"), htons(hdr->source_port));
  printf(" Destination port: " BLUE("%d") "\n", htons(hdr->dest_port));
}
