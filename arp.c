#include <stdio.h>
#include <netinet/if_ether.h>
#include "arp.h"
#include "ethernet.h"

void arp_packet(const u_char* packet) {
  struct my_arp_packet *pkt;
  pkt = (struct my_arp_packet *) packet;
  char sender_mac[18];

  mac_address(pkt->sender_mac, sender_mac);
  printf("\tARP packet - hardware type: %d op: %s sender MAC: %s\n", ntohs(pkt->hardware_type), ntohs(pkt->operation) == 1 ? "request" : "reply", sender_mac);
}

// next step: print sender and target MAC and IP addresses
