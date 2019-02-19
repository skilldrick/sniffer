// https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol
struct my_icmp_header {
  unsigned char type;
  unsigned char code;
  unsigned short checksum;
  unsigned long rest;
};

void icmp(const unsigned char* packet);


