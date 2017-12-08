
CROSS_COMPILE ?=

CC = ${CROSS_COMPILE}gcc
AS = ${CROSS_COMPILE}as
LD = ${CROSS_COMPILE}gcc

CFLAGS=-Wall -g -pthread
LDFLAGS=-pthread
LOADLIBES=-lrt

APPLICATIONS:=              \
	exemple-01          \
	exemple-02          \
	exemple-03          \
	exemple-04          \
	exemple-05          \
	exemple-06          \
	exemple-07          \
	exemple-08          \
	exemple-09          \
	exemple-10          \
	exemple-11          \
	exemple-12          \


all: ${APPLICATIONS}

clean::
	rm -f ${APPLICATIONS} *.o *~
	
