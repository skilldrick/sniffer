#pragma once

#include <stdlib.h>
#include "ip.h"
#include "tcp.h"

struct Connection {
  char               key[50];
  uint32_t           seq_offset;
  uint32_t           ack_offset;
  struct Connection* next;
};

struct Connection* new_connection(char* key);

struct Connection* find(struct Connection* head, struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr);

struct Connection* find_by_key(struct Connection* head, char* key);

int length(struct Connection* head);

void generate_forward_key(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr, char* key);

void generate_reverse_key(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr, char* key);

void generate_key(uint8_t* source_ip, uint8_t* dest_ip, uint16_t source_port, uint16_t dest_port, char* key);
