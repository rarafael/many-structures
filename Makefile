CC=cc
CFLAGS=-Wall -Wextra -std=c99 -Wpedantic -O3 -ggdb

all: bin/single-list bin/double-list

bin/single-list: src/single-list.c
	$(CC) $(CFLAGS) $^ -o $@

bin/double-list: src/double-list.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm bin/*
