// use `make && ./sniffer` to run

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/if_ether.h>
#include "ethernet.h"
#include "ip.h"
#include "arp.h"
#include "icmp.h"
#include "tcp.h"
#include "udp.h"
#include "color.h"

// we don't really care about pkthdr as that's just a pcap thing
// packet is the actual ethernet packet
void my_callback(unsigned char *args,const struct pcap_pkthdr* pkthdr,const unsigned char* packet) {
  u_short ether_type = ethernet_header(packet);

  const unsigned char* ether_payload = packet + sizeof(struct my_ether_header);

  if (ether_type == ETHERTYPE_IP) {
    struct my_ip_header* ip_hdr = ip_header(ether_payload);
    unsigned char ip_protocol = ip_hdr->protocol;
    const unsigned char* ip_payload = ether_payload + IP_HEADER_LENGTH(ip_hdr) * 4;

    if (ip_protocol == IP_ICMP) {
      icmp(ip_payload);
    } else if (ip_protocol == IP_TCP) {
      tcp_header(ip_payload);
    } else if (ip_protocol == IP_UDP) {
      udp_header(ip_payload);
    } else {
      printf("\t\tunknown IP protocol %d\n", ip_protocol);
    }
  } else if (ether_type == ETHERTYPE_ARP) {
    arp_packet(ether_payload);
  } else if (ether_type == 0x86dd) {
    printf("\tIPv6 packet\n");
  } else if (ether_type < 0x600) {
    // Instances of this case so far have been STP (spanning tree protocol)
    // see https://en.wikipedia.org/wiki/IEEE_802.3 (Same as Ethernet II (above) except Type field is replaced by Length, and an 802.2 LLC header follows the 802.3 header.)
    // and https://en.wikipedia.org/wiki/IEEE_802.2
    printf("\tNo EtherType. Ethernet frame size: " BLUE("%d\n"), ether_type);
  } else {
    printf("\tunknown EtherType %#06x\n", ether_type);
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

