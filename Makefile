# i have no idea what i'm doing

objects = sniffer.o ethernet.o ip.o arp.o

sniffer : $(objects)
	gcc -o sniffer $(objects) -lpcap

sniffer.o : ethernet.h ip.h
