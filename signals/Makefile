CC      = gcc
CFLAGS  = -o2 -Wall
LDFLAGS = -s -lm

.PHONY : all clean

all: obsluga.x wysylaj.x grupa.x

obsluga.x : obsluga.o procinfo.o
	$(CC) $(LDFLAGS) -o $@ $^

obsluga.o : obsluga.c procinfo.h
	$(CC) $(CFLAGS) -c -o obsluga.o obsluga.c

wysylaj.x : wysylaj.o procinfo.o
	$(CC) $(LDFLAGS) -o $@ $^

wysylaj.o : wysylaj.c procinfo.h
	$(CC) $(CFLAGS) -c -o wysylaj.o wysylaj.c


procinfo.o : procinfo.c procinfo.h
	$(CC) $(CFLAGS) -c -o procinfo.o procinfo.c

grupa.x : grupa.o procinfo.o
	$(CC) $(LDFLAGS) -o $@ $^

grupa.o : grupa.c procinfo.h
	$(CC) $(CFLAGS) -c -o grupa.o grupa.c


clean:
	$(RM) *.o *.x


