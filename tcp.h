struct my_tcp_header {
  unsigned short source_port;
  unsigned short dest_port;
  unsigned long seq_number;
  unsigned long ack_number;
};

void tcp_header(const unsigned char* packet);
