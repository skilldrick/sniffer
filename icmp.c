#include <stdio.h>
#include <netinet/if_ether.h>
#include "icmp.h"
#include "color.h"

void icmp(const uint8_t* packet) {
  struct my_icmp_header* pkt;
  pkt = (struct my_icmp_header*) packet;

  printf("\t\tICMP: ");
  if (pkt->type == 0) {
    printf(BLUE("echo reply"));
  } else if (pkt->type == 8) {
    printf(BLUE("echo request"));
  } else {
    printf("Type: " BLUE("%d") " Code: " BLUE("%d"), pkt->type, pkt->code);
  }

  if (pkt->type == 0 || pkt->type == 8) {
    ping(packet + sizeof(struct my_icmp_header));
  }

  printf("\n");
}

void ping(const uint8_t* packet) {
  struct echo* e;
  e = (struct echo*) packet;

  printf(" Identifier: " BLUE("%d"), ntohs(e->identifier));
  printf(" Sequence number: " BLUE("%d"), ntohs(e->sequence_number));
}
