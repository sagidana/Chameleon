CC=gcc
CFLAGS=-I.
DEPS = socks.h
BINDIR = ../bin/

%.o: %.c $(DEPS)
	$(CC) -c -o $(BINDIR)$@ $< $(CFLAGS)

make: bot.o socks.o 
	$(CC) -o $(BINDIR)bot $(BINDIR)bot.o $(BINDIR)socks.o $(CFLAGS)