#include <netinet/if_ether.h>
#include <stdio.h>
#include "tcp.h"
#include "color.h"
#include "connections.h"

void tcp_header(const uint8_t* packet, struct my_ip_header* ip_hdr) {
  struct my_tcp_header* hdr;
  hdr = (struct my_tcp_header *) packet;
  printf("\t\tTCP - Source port: " BLUE("%d"), ntohs(hdr->source_port));
  printf(" Destination port: " BLUE("%d"), ntohs(hdr->dest_port));

  printf(" Sequence number: " BLUE("%u"), ntohl(hdr->seq_number));

  char key[50];
  generate_key(ip_hdr, hdr, key);
  struct Connection* conn = find(get_connections(), key);

  if (conn) {
    printf(" Base sequence number: " BLUE("%u"), conn->seq_offset);
  } else {
    printf(" Not found: %s ", key);
  }

  printf(" Acknowledgement number: " BLUE("%u"), ntohl(hdr->ack_number));

  printf(" Data offset: " BLUE("%d bytes"), TCP_DATA_OFFSET_BYTES(hdr));

  printf(" Flags:");

  // TODO: on SYN, add an entry to a table so we can track the sequence numbers
  if (TCP_FIN(hdr)) {
    printf(BLUE(" FIN"));
  }
  if (TCP_SYN(hdr)) {
    printf(BLUE(" SYN"));
    struct Connection* conn = new_connection(ip_hdr, hdr);
    conn->seq_offset = ntohl(hdr->seq_number);
  }
  if (TCP_ACK(hdr)) {
    printf(BLUE(" ACK"));
  }


  printf("\nPointer in tcp: %p\n", get_connections());
  /*
  printf("\n");
  for (int i = 0; i < 20; i++) {
    printf("%02x.", (uint8_t) packet[i]);
  }
  */

  printf("\n");
}
