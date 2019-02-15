#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/if_ether.h>

// ethernet header is:
// 6 bytes of destination MAC address
// 6 bytes of source MAC address
// 2 bytes of EtherType
struct my_ether_header {
  u_char dest[6];
  u_char source[6];
  u_short ether_type;
};

void mac_address(u_char* bytes, char* addr) {
  sprintf(
    addr,
    "%x:%x:%x:%x:%x:%x",
    bytes[0],
    bytes[1],
    bytes[2],
    bytes[3],
    bytes[4],
    bytes[5]
  );
}

struct my_ip_header {
  u_char version_and_ihl;
  u_char dscp_and_ecn;
  u_short length;
  u_short flags_and_fragment_offset;
  u_char ttl;
  u_char protocol;
  u_short checksum;
  u_char source_ip[4];
  u_char dest_ip[4];
};

void ip_address(u_char* bytes, char* addr) {
  sprintf(
    addr,
    "%d.%d.%d.%d",
    // this is janky - should convert between network and host byte order
    bytes[2],
    bytes[3],
    bytes[0],
    bytes[1]
  );
}

// returns the ether_type, which defines the type of the content
u_short ethernet_header(const u_char* packet) {
  struct my_ether_header *hdr;
  hdr = (struct my_ether_header *) packet;

  char source[18];
  char dest[18];
  u_short ether_type;
  mac_address(hdr->source, source);
  mac_address(hdr->dest, dest);
  ether_type = htons(hdr->ether_type);

  printf("Ethernet header - source: %s destination: %s EtherType: %#06x\n", source, dest, ether_type);

  return ether_type;
}

void ip_header(const u_char* packet) {
  struct my_ip_header *hdr;
  hdr = (struct my_ip_header *) packet;

  char source[16];
  char dest[16];
  ip_address(hdr->source_ip, source);
  ip_address(hdr->dest_ip, dest);

  printf("\tIP header - IPv%d source: %s destination: %s\n", ((hdr->version_and_ihl) & 0xf0) >> 4, source, dest);
}

// assuming this is an ipv4 arp packet
struct my_arp_packet {
  u_short hardware_type;
};

void arp_packet(const u_char* packet) {
  struct my_arp_packet *pkt;
  pkt = (struct my_arp_packet *) packet;
  printf("\tARP packet - hardware type: %d\n", ntohs(pkt->hardware_type));
}

// we don't really care about pkthdr as that's just a pcap thing
// packet is the actual ethernet packet
void my_callback(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet) {
  u_short ether_type = ethernet_header(packet);

  const u_char* payload = packet + sizeof(struct my_ether_header);

  if (ether_type == ETHERTYPE_IP) {
    ip_header(payload);
  } else if (ether_type == ETHERTYPE_ARP) {
    arp_packet(payload);
  }
}

int main(int argc,char **argv) {
  char *dev;
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t* descr;

  dev = pcap_lookupdev(errbuf);
  if(dev == NULL) {
    printf("pcap_lookupdev(): %s\n",errbuf); exit(1);
  }

  // open dev for reading
  descr = pcap_open_live(dev,BUFSIZ,0,1000,errbuf);
  if(descr == NULL) {
    printf("pcap_open_live(): %s\n",errbuf); exit(1);
  }

  // loop over packets forever
  pcap_loop(descr,-1,my_callback,NULL);

  return 0;
}

