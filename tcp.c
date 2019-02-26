#include <netinet/if_ether.h>
#include <stdio.h>
#include "tcp.h"
#include "color.h"
#include "connections.h"

// linked list of connections
static struct Connection* connections = NULL;

void tcp_header(const uint8_t* packet, struct my_ip_header* ip_hdr) {
  struct my_tcp_header* hdr;
  hdr = (struct my_tcp_header *) packet;
  printf("\t\tTCP - Source port: " BLUE("%d"), ntohs(hdr->source_port));
  printf(" Destination port: " BLUE("%d"), ntohs(hdr->dest_port));

  printf("\n\t\t\tSequence number: " BLUE("%u"), ntohl(hdr->seq_number));

  char key[50];
  generate_key(ip_hdr, hdr, key);
  struct Connection* conn = find(connections, key);

  if (conn) {
    printf(" Relative sequence number: " BLUE("%u"), ntohl(hdr->seq_number) - conn->seq_offset);
  }

  printf("\n\t\t\tAcknowledgement number: " BLUE("%u"), ntohl(hdr->ack_number));

  if (conn && conn->ack_offset) {
    printf(" Relative acknowledgement number: " BLUE("%u"), ntohl(hdr->ack_number) - conn->ack_offset);
  }


  printf("\n\t\t\tData offset: " BLUE("%d bytes"), TCP_DATA_OFFSET_BYTES(hdr));

  printf(" Flags:");
  if (TCP_FIN(hdr)) {
    printf(BLUE(" FIN"));
  }
  if (TCP_SYN(hdr)) {
    printf(BLUE(" SYN"));
  }
  if (TCP_ACK(hdr)) {
    printf(BLUE(" ACK"));
  }

  // on SYN, initialize a new connection
  if (TCP_SYN(hdr)) {
    struct Connection* conn = new_connection(ip_hdr, hdr);
    conn->seq_offset = ntohl(hdr->seq_number);
    conn->ack_offset = 0;

    // add to head of linked list (TODO: make a method)
    conn->next = connections;
    connections = conn;

    // on SYN ACK, update the ack offset of the server as the syn offset of the client
    if (TCP_ACK(hdr)) {
      char reverse_key[50];
      generate_key(ip_hdr, hdr, reverse_key);
      struct Connection* reverse_conn = find(connections, reverse_key);
      if (conn && reverse_conn) {
        // TODO: this is still wrong
        conn->ack_offset = reverse_conn->seq_offset;
        reverse_conn->ack_offset = conn->seq_offset;
      }
    }
  }

  printf("\n");
}
