// https://en.wikipedia.org/wiki/IPv4#Header
struct my_ip_header {
  u_char version_and_ihl;
  u_char dscp_and_ecn;
  u_short length;
  u_short identification;
  u_short flags_and_fragment_offset;
  u_char ttl;
  u_char protocol;
  u_short checksum;
  u_char source_ip[4];
  u_char dest_ip[4];
};

#define IP_HEADER_LENGTH(hdr)  ((hdr)->version_and_ihl & 0x0f)
#define IP_VERSION(hdr)  (((hdr)->version_and_ihl & 0xf0) >> 4)

void ip_address(u_char* bytes, char* addr);

struct my_ip_header* ip_header(const u_char* packet);

#define IP_ICMP 1
#define IP_TCP 6
#define IP_UDP 17

