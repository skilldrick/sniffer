// assuming this is an ipv4 arp packet
struct my_arp_packet {
  u_short hardware_type;
  u_short protocol_type;
  u_char hlen;
  u_char plen;
  u_short operation;
  u_char sender_mac[6];
  u_char sender_ip[6];
};

void arp_packet(const u_char* packet);
