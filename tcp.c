#include <netinet/if_ether.h>
#include <stdio.h>
#include "tcp.h"
#include "color.h"

void tcp_header(const unsigned char* packet) {
  struct my_tcp_header* hdr;
  hdr = (struct my_tcp_header *) packet;
  printf("\t\tTCP - Source port: " BLUE("%d"), ntohs(hdr->source_port));
  printf(" Destination port: " BLUE("%d"), ntohs(hdr->dest_port));

  printf(" Sequence number: " BLUE("%u"), ntohl(hdr->seq_number));
  printf(" Acknowledgement number: " BLUE("%u"), ntohl(hdr->ack_number));

  printf("\n");
}
