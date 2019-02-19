// https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol
struct my_icmp_packet {
  unsigned char type;
  unsigned char code;
  unsigned short checksum;
  unsigned long rest;
};

void icmp_packet(const unsigned char* packet);
