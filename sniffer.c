// use `make && ./sniffer` to run

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/if_ether.h>
#include "ethernet.h"
#include "ip.h"

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

