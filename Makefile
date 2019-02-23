# i have no idea what i'm doing

objects = sniffer.o ethernet.o ip.o arp.o icmp.o udp.o tcp.o connections.o

sniffer : $(objects)
	cc -Wall -o sniffer $(objects) -lpcap

sniffer.o : ethernet.h ip.h arp.h icmp.h udp.h tcp.h connections.h

tcp.o : tcp.h connections.h

connections.o : connections.h

clean :
	rm sniffer *.o
