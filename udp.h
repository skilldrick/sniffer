struct my_udp_header {
  uint16_t source_port;
  uint16_t dest_port;
  uint16_t length;
  uint16_t checksum;
};

void udp_header(const uint8_t* packet);
