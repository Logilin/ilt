##############################################################################
## Exemple de la formation "Temps-reel sous Linux"
##
## Christophe Blaess 2010-2023
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################


CROSS_COMPILE ?=

CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)gcc

CFLAGS=-Wall -g -pthread
LDFLAGS=-pthread
LOADLIBES=-lrt


EXE:=                 \
  example-IV-01        \
  example-IV-02        \
  example-IV-03        \
  example-IV-04        \
  example-IV-05        \
  example-IV-06        \
  example-IV-07        \
  example-IV-08        \
  example-IV-09        \
  example-IV-10        \
  example-IV-11        \
  example-IV-12        \


.PHONY: all
all: $(EXE)


.PHONY: clean
clean::
	rm -f $(EXE) *.o *~

