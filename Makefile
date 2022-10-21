LDFLAGS=-lm
CFLAGS=-O2
all: onebit

.PHONY: debug
debug: CFLAGS=-g -O0
debug: onebit

.PHONY: clean
clean:
	rm onebit
