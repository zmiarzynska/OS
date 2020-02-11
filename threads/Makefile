CC      = gcc
CFLAGS  = -o2 -Wall
LDFLAGS = -s -lm


.PHONY : all clean 

all: watki.x

watki.x: watki.o 
	$(CC) $(LDFLAGS) -o $@ $^ -lpthread

watki.o: watki.c
	$(CC) $(CFLAGS) -c -o $@ $^





clean : 
	rm -f *.o *.x 
