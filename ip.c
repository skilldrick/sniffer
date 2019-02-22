#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/if_ether.h>
#include "ip.h"
#include "color.h"

void ip_address(uint8_t* bytes, char* addr) {
  sprintf(
    addr,
    "%d.%d.%d.%d",
    bytes[0],
    bytes[1],
    bytes[2],
    bytes[3]
  );
}

int get_name(char* ip_address, char* output) {
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  inet_pton(AF_INET, ip_address, &addr.sin_addr);

  // http://man7.org/linux/man-pages/man3/getnameinfo.3.html
  int res = getnameinfo(
      (struct sockaddr*) &addr,
      sizeof(addr),
      output,
      NI_MAXHOST,
      NULL,
      0,
      NI_NAMEREQD
  );

  return res;
}

void print_name(char* ip_address) {
  char node[NI_MAXHOST];

  if (!get_name(ip_address, node)) {
    printf("(" BLUE("%s") ")", node);
  } else {
    printf("(?)");
  }
}

struct my_ip_header* ip_header(const uint8_t* packet) {
  struct my_ip_header *hdr;
  hdr = (struct my_ip_header *) packet;

  char source[16];
  char dest[16];
  ip_address(hdr->source_ip, source);
  ip_address(hdr->dest_ip, dest);


  printf("\tIP header - IPv%d", IP_VERSION(hdr));
  printf(" Source: " BLUE("%s "), source);
  print_name(source);
  printf(" Destination: " BLUE("%s "), dest);
  print_name(dest);
  printf(" TTL: " BLUE("%d\n"), hdr->ttl);

  return hdr;
}

