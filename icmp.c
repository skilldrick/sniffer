#include <stdio.h>
#include "icmp.h"
#include "color.h"

void icmp_packet(const unsigned char* packet) {
  struct my_icmp_packet* pkt;
  pkt = (struct my_icmp_packet*) packet;

  printf("\tICMP packet: %d %d\n", pkt->type, pkt->code);
}
