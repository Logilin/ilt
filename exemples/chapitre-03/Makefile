
CFLAGS=-Wall -g

CROSS_COMPILE?=

CC=$(CROSS_COMPILE)gcc

.PHONY: all
all: hello

hello: hello.c
	${CC} ${CFLAGS} hello.c -o hello 

.PHONY: clean
clean: 
	rm -f hello


