CC      = gcc
CFLAGS  = -o2 -Wall
LDFLAGS = -s -lm

.PHONY : all clean

all: prodkons.x prod.x kons.x fifo.x

prodkons.x : prodkons.o
	$(CC) $(LDFLAGS) -o $@ $^

prodkons.o : prodkons.c 
	$(CC) $(CFLAGS) -c -o $@ $^

fifo.x : fifo.o 
	$(CC) $(LDFLAGS) -o $@ $^

fifo.o : fifo.c 
	$(CC) $(CFLAGS) -c -o $@ $^

prod.x : prod.o
	$(CC) $(LDFLAGS) -o $@ $^

prod.o : prod.c 
	$(CC) $(CFLAGS) -c -o $@ $^

kons.x : kons.o
	$(CC) $(LDFLAGS) -o $@ $^

kons.o : kons.c 
	$(CC) $(CFLAGS) -c -o $@ $^



clean:
	$(RM) *.o *.x schowek* potok*

