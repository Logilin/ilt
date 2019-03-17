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
  exemple-IV-01        \
  exemple-IV-02        \
  exemple-IV-03        \
  exemple-IV-04        \
  exemple-IV-05        \
  exemple-IV-06        \
  exemple-IV-07        \
  exemple-IV-08        \
  exemple-IV-09        \
  exemple-IV-10        \
  exemple-IV-11        \


.PHONY: all
all: ${EXE}


.PHONY: clean
clean::
	rm -f ${EXE} *.o *~

