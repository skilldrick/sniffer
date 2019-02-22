// https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol
struct my_icmp_header {
  uint8_t type;
  uint8_t code;
  uint16_t checksum;
};

struct echo {
  uint16_t identifier;
  uint16_t sequence_number;
};

void icmp(const uint8_t* packet);

void ping(const uint8_t* packet);
