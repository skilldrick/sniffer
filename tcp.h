#pragma once

#include <stdio.h>
#include "ip.h"

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
#define TCP_FIN(hdr)  ((hdr)->flags & (1 << 0))
#define TCP_SYN(hdr)  ((hdr)->flags & (1 << 1))
#define TCP_ACK(hdr)  ((hdr)->flags & (1 << 4))

struct my_tcp_header* tcp_header(const uint8_t* packet, struct my_ip_header* ip_hdr);

// linked list of connections
static struct Connection* connections = NULL;

struct Connection* get_connections();
