CC = gcc
CFLAGS = -Wall -o
.PHONY: all clean

all: klient.x serwer.x

klient.x: klient.c
	$(CC) $(CFLAGS) klient.x klient.c 

serwer.x: serwer.c
	$(CC) $(CFLAGS) serwer.x serwer.c

clean:
	$(RM) *.o *.x
