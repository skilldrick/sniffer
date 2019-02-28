#include "ip.h"
#include "tcp.h"
#include "http.h"
#include "connections.h"
#include <stdio.h>
#include <string.h>

void http(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr) {
  int ip_header_length = IP_HEADER_LENGTH_BYTES(ip_hdr);
  int tcp_data_offset = TCP_DATA_OFFSET_BYTES(tcp_hdr);
  int tcp_and_ip_offset = tcp_data_offset + ip_header_length;
  int tcp_payload_length = ip_hdr->total_length - tcp_and_ip_offset;
  const uint8_t* tcp_payload = (uint8_t*) tcp_hdr + tcp_data_offset;

  char payload[tcp_payload_length + 1];

  strncpy(payload, (char *) tcp_payload, 10/*tcp_payload_length*/);

  // Because of keep-alive, this connection will be reused for multiple requests
  struct Connection* conn = find(get_connections(), ip_hdr, tcp_hdr);
  printf("Connection: %p Payload: %s\n", conn, payload);
}
