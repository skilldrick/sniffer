# i have no idea what i'm doing

objects = sniffer.o ethernet.o ip.o arp.o icmp.o udp.o tcp.o

sniffer : $(objects)
	cc -o sniffer $(objects) -lpcap

sniffer.o : ethernet.h ip.h arp.h icmp.h udp.h tcp.h

tcp.o : tcp.h

clean :
	rm sniffer *.o
