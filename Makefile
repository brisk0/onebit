LDFLAGS=-lm
CFLAGS=-O2 -Wall
all: onebit

.PHONY: debug
debug: CFLAGS=-g -O0 -Wall
debug: onebit

.PHONY: clean
clean:
	rm onebit
