CC=cc
CFLAGS=-Wall -Wextra -std=c99 -Wpedantic -O3 -ggdb -Wno-unused-variable
BINDIR=bin

all: $(BINDIR)\
     $(BINDIR)/single-list\
     $(BINDIR)/double-list\
     $(BINDIR)/hashmap 

$(BINDIR):
	mkdir bin

$(BINDIR)/single-list: src/single-list.c
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/double-list: src/double-list.c
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/hashmap: src/hashmap.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm bin/*
