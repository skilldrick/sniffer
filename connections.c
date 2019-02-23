#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/if_ether.h>
#include "connections.h"

int length(struct Connection* head) {
  struct Connection* cursor = head;
  int i = 0;

  while (cursor) {
    cursor = cursor->next;
    i++;
  }

  return i;
}

struct Connection* find(struct Connection* head, char* key) {
  struct Connection* cursor = head;

  printf("\ncursor->key: %s key: %s\n", cursor->key, key);
  while (cursor) {
    printf("\ncursor->key: %s key: %s\n", cursor->key, key);
    if (!strcmp(cursor->key, key)) {
      return cursor;
    }

    cursor = cursor->next;
  }

  return NULL;
}

//TODO: all these methods should return head
struct Connection* new_connection(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr) {
  char key[50];
  generate_key(ip_hdr, tcp_hdr, key);

  struct Connection* conn = (struct Connection*) malloc(sizeof(struct Connection));
  if(conn == NULL) {
    printf("Error creating Connection.\n");
    exit(0);
  }

  strcpy(conn->key, key);

  conn->next = connections;
  connections = conn;

  printf("\nkey: %s num: %d\n", conn->key, length(connections));

  printf("\nPointer: %p\n", connections);

  return conn;
};

// this will ip:port ip:port, e.g.
// 111.111.111.111:80 222.222.222.222:45678
void generate_key(struct my_ip_header* ip_hdr, struct my_tcp_header* tcp_hdr, char* key) {
  ip_address(ip_hdr->source_ip, key);
  sprintf(key + strlen(key), ":%d ", ntohs(tcp_hdr->source_port));

  ip_address(ip_hdr->dest_ip, key + strlen(key));
  sprintf(key + strlen(key), ":%d", ntohs(tcp_hdr->dest_port));
}


