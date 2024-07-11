##############################################################################
## Exemple de la formation "Temps-reel sous Linux"
##
## Christophe Blaess 2010-2024
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

CROSS_COMPILE ?=

CC ?= $(CROSS_COMPILE)gcc
AS ?= $(CROSS_COMPILE)as
LD ?= $(CROSS_COMPILE)gcc

CFLAGS += -Wall -g -pthread
LDFLAGS += -pthread
LOADLIBES += -lrt


EXE:=                 \
  example-V-01       \


.PHONY: all
all: $(EXE)


.PHONY: clean
clean::
	rm -f $(EXE) *.o *~


