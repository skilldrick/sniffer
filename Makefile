# i have no idea what i'm doing
sniffer : sniffer.o ethernet.o ip.o
	gcc -o sniffer sniffer.o ethernet.o ip.o -lpcap

sniffer.o : sniffer.c ethernet.h ip.h
	gcc -c sniffer.c

ethernet.o : ethernet.c
	gcc -c ethernet.c

ip.o : ip.c
	gcc -c ip.c
