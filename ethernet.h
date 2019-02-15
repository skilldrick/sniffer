// ethernet header is:
// 6 bytes of destination MAC address
// 6 bytes of source MAC address
// 2 bytes of EtherType
struct my_ether_header {
  u_char dest[6];
  u_char source[6];
  u_short ether_type;
};

void mac_address(u_char* bytes, char* addr);

u_short ethernet_header(const u_char* packet);
