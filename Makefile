# i have no idea what i'm doing

objects = sniffer.o ethernet.o ip.o arp.o icmp.o

sniffer : $(objects)
	cc -o sniffer $(objects) -lpcap

sniffer.o : ethernet.h ip.h arp.h icmp.h

clean :
	rm sniffer *.o
