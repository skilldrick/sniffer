struct my_udp_header {
  unsigned short source_port;
  unsigned short dest_port;
  unsigned short length;
  unsigned short checksum;
};

void udp_header(const unsigned char* packet);
