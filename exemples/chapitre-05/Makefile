##############################################################################
## Exemple de la formation "Temps-reel Linux et Xenomai"
##
## Christophe Blaess 2010-2018
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

CROSS_COMPILE ?=

CC = ${CROSS_COMPILE}gcc
AS = ${CROSS_COMPILE}as
LD = ${CROSS_COMPILE}gcc

CFLAGS=-Wall -g -pthread
LDFLAGS=-pthread
LOADLIBES=-lrt


EXE:=                 \
  exemple-V-01       \


.PHONY: all
all: ${EXE}


.PHONY: clean
clean::
	rm -f ${EXE} *.o *~


