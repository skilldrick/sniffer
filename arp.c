#include <stdio.h>
#include <netinet/if_ether.h>
#include "arp.h"
#include "ethernet.h"
#include "ip.h"


void arp_packet(const u_char* packet) {
  struct my_arp_packet *pkt;
  pkt = (struct my_arp_packet *) packet;
  char mac[18];
  char ip[16];
  u_short hardware_type = ntohs(pkt->hardware_type);

  printf("\tARP packet - hardware type: ");

  if (hardware_type == 1) {
    printf("ethernet");
  } else {
    printf("%d", hardware_type);
  }

  printf(" op: %s\n", ntohs(pkt->operation) == 1 ? "request" : "reply");

  mac_address(pkt->sender_mac, mac);
  printf("\t  sender MAC: %s", mac);

  mac_address(pkt->target_mac, mac);
  printf(" target MAC: %s\n", mac);

  ip_address(pkt->sender_ip, ip);
  printf("\t  sender IP: %s", ip);

  ip_address(pkt->target_ip, ip);
  printf(" target IP: %s", ip);

  printf("\n");
}
