#include <stdio.h>
#include <netinet/if_ether.h>
#include "arp.h"
#include "ethernet.h"
#include "ip.h"
#include "color.h"


void arp_packet(const u_char* packet) {
  struct my_arp_packet *pkt;
  pkt = (struct my_arp_packet *) packet;
  char mac[18];
  char ip[16];
  u_short hardware_type = ntohs(pkt->hardware_type);

  printf("\tARP packet - Hardware type: ");

  if (hardware_type == 1) {
    printf(BLUE("ethernet"));
  } else {
    printf(BLUE("%d"), hardware_type);
  }

  printf(" Op: " BLUE("%s\n"), ntohs(pkt->operation) == 1 ? "request" : "reply");

  mac_address(pkt->sender_mac, mac);
  printf("\t  Sender MAC: " BLUE("%s"), mac);

  mac_address(pkt->target_mac, mac);
  printf(" Target MAC: " BLUE("%s\n"), mac);

  ip_address(pkt->sender_ip, ip);
  printf("\t  Sender IP: " BLUE("%s"), ip);

  ip_address(pkt->target_ip, ip);
  printf(" Target IP: " BLUE("%s"), ip);

  printf("\n");
}
