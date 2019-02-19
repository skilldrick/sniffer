// https://en.wikipedia.org/wiki/Address_Resolution_Protocol
// assuming this is an ipv4 arp packet
struct my_arp_packet {
  u_short hardware_type;
  u_short protocol_type;
  u_char hlen;
  u_char plen;
  u_short operation;
  u_char sender_mac[6];
  u_char sender_ip[4];
  u_char target_mac[6];
  u_char target_ip[4];
};

void arp_packet(const u_char* packet);
