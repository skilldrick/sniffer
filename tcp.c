#include <netinet/if_ether.h>
#include <stdio.h>
#include "tcp.h"
#include "color.h"

void tcp_header(const uint8_t* packet) {
  struct my_tcp_header* hdr;
  hdr = (struct my_tcp_header *) packet;
  printf("\t\tTCP - Source port: " BLUE("%d"), ntohs(hdr->source_port));
  printf(" Destination port: " BLUE("%d"), ntohs(hdr->dest_port));

  printf(" Sequence number: " BLUE("%u"), ntohl(hdr->seq_number));
  printf(" Acknowledgement number: " BLUE("%u"), ntohl(hdr->ack_number));

  printf(" Data offset: " BLUE("%d bytes"), TCP_DATA_OFFSET_BYTES(hdr));

  printf("\n");
  for (int i = 0; i < 20; i++) {
    printf("%02x.", (uint8_t) packet[i]);
  }

  printf("\n");
}
