// https://en.wikipedia.org/wiki/Address_Resolution_Protocol
// assuming this is an ipv4 arp packet
struct my_arp_packet {
  uint16_t hardware_type;
  uint16_t protocol_type;
  uint8_t hlen;
  uint8_t plen;
  uint16_t operation;
  uint8_t sender_mac[6];
  uint8_t sender_ip[4];
  uint8_t target_mac[6];
  uint8_t target_ip[4];
};

void arp_packet(const uint8_t* packet);
