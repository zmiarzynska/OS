CC      = gcc
CFLAGS  = -o2 -Wall
LDFLAGS = -s -lm

.PHONY : all clean

all: prog.x powielacz.x semuse.x 

prog.x : prog.o libsem.a
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lsem


prog.o : prog.c 
	$(CC) $(CFLAGS) -c -o $@ $^

powielacz.x : powielacz.o libsem.a 
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lsem


powielacz.o : powielacz.c 
	$(CC) $(CFLAGS) -c -o $@ $^

semuse.x : semuse.o libsem.a 
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lsem

semuse.o : semuse.c 
	$(CC) $(CFLAGS) -c -o $@ $^

sem.o : sem.c
	$(CC) -c sem.c

libsem.a: sem.o 
	ar rv libsem.a sem.o



clean : 
	rm -f *.o *.x
