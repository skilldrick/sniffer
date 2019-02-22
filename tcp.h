struct my_tcp_header {
  uint16_t source_port;
  uint16_t dest_port;
  uint32_t seq_number;
  uint32_t ack_number;
  uint8_t data_offset_etc;
  uint8_t flags;
  uint16_t window_size;
  uint16_t checksum;
  uint16_t urg_pointer;
};

#define TCP_DATA_OFFSET_BYTES(hdr)  ((((hdr)->data_offset_etc & 0xf0) >> 4) * 4)

void tcp_header(const uint8_t* packet);
