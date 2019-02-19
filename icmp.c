#include <stdio.h>
#include "icmp.h"
#include "color.h"

void icmp(const unsigned char* packet) {
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

  printf("\n");
}
