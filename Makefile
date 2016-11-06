all: server client

server: ipsxx.o
	gcc -o server ipsxx.o

server.o: ipsxx.c
	gcc -c ipsxx.c

client: ipcx.o
	gcc -o client ipcx.o

client.o: ipcx.c
	gcc -c ipcx.c

clean:
	rm *.o client server

