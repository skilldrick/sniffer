#include <netinet/if_ether.h>
#include <stdio.h>
#include "ethernet.h"
#include "color.h"

void mac_address(uint8_t* bytes, char* addr) {
  sprintf(
    addr,
    "%x:%x:%x:%x:%x:%x",
    bytes[0],
    bytes[1],
    bytes[2],
    bytes[3],
    bytes[4],
    bytes[5]
  );
}

// returns the ether_type, which defines the type of the content
uint16_t ethernet_header(const uint8_t* packet) {
  struct my_ether_header *hdr;
  hdr = (struct my_ether_header *) packet;

  char source[18];
  char dest[18];
  uint16_t ether_type;
  mac_address(hdr->source, source);
  mac_address(hdr->dest, dest);

  printf("Ethernet header - ");
  printf("Source: " BLUE("%s") " Destination: " BLUE("%s\n"), source, dest);

  return htons(hdr->ether_type);
}
