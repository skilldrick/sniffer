#pragma once

#include "stdint.h"

// https://en.wikipedia.org/wiki/IPv4#Header
struct my_ip_header {
  uint8_t version_and_ihl;
  uint8_t dscp_and_ecn;
  uint16_t total_length;
  uint16_t identification;
  uint16_t flags_and_fragment_offset;
  uint8_t ttl;
  uint8_t protocol;
  uint16_t checksum;
  uint8_t source_ip[4];
  uint8_t dest_ip[4];
};

#define IP_HEADER_LENGTH_BYTES(hdr)  (((hdr)->version_and_ihl & 0x0f) * 4)
#define IP_VERSION(hdr)  (((hdr)->version_and_ihl & 0xf0) >> 4)

void ip_address(uint8_t* bytes, char* addr);

struct my_ip_header* ip_header(const uint8_t* packet);

#define IP_ICMP 1
#define IP_TCP 6
#define IP_UDP 17
