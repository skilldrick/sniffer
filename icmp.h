// https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol
struct my_icmp_header {
  unsigned char type;
  unsigned char code;
  unsigned short checksum;
};

struct echo {
  unsigned short identifier;
  unsigned short sequence_number;
};

void icmp(const unsigned char* packet);

void ping(const unsigned char* packet);
