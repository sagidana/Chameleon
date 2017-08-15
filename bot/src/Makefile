CC=gcc
CFLAGS=-I. -m32
DEPS = socks.h utils.h
BINDIR = ../bin/

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $(BINDIR)$@ $< 

make: bot.o socks.o utils.o
	$(CC) $(CFLAGS) -o $(BINDIR)bot $(BINDIR)bot.o $(BINDIR)socks.o $(BINDIR)utils.o