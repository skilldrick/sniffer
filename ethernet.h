// https://en.wikipedia.org/wiki/Ethernet_frame#Ethernet_II
// ethernet header is:
// 6 bytes of destination MAC address
// 6 bytes of source MAC address
// 2 bytes of EtherType
struct my_ether_header {
  uint8_t dest[6];
  uint8_t source[6];
  uint16_t ether_type;
};

void mac_address(uint8_t* bytes, char* addr);

uint16_t ethernet_header(const uint8_t* packet);

#define ETHERTYPE_IPV6 0x86dd
