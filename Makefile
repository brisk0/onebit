LDFLAGS=-lm
CFLAGS=-g -O2 -Wall -Wpedantic -std=c17

.PHONY: all
all: onebit

.PHONY: clean
clean:
	rm onebit
