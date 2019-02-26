#pragma once

#include "ip.h"
#include "tcp.h"

struct Connection {
  char               key[50];
  uint32_t           seq_offset;
  uint32_t           ack_offset;
  struct Connection* next;
};

struct Connection* new_connection(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr);

int length(struct Connection* head);

struct Connection* find(struct Connection* head, char* key);

void generate_key(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr, char* key);

void generate_reverse_key(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr, char* key);
