##############################################################################
## Exemple de la formation "Temps-reel sous Linux"
##
## Christophe Blaess 2010-2026
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

APPLICATIONS:=      \
  example-VII-01    \
  example-VII-02    \
  example-VII-03    \
  example-VII-04    \
  example-VII-05    \
  example-VII-06    \

CFLAGS += -Wall -g -pthread
LDFLAGS += -pthread
LOADLIBES += -lrt

CROSS_COMPILE ?=
ARCH          ?=
KERNEL_DIR    ?= /lib/modules/$(shell uname -r)/build
MODULE_DIR    := $(shell pwd)

CC = $(CROSS_COMPILE)gcc

.PHONY: all
all: $(APPLICATIONS)

.PHONY: clean
clean:
	rm -f $(APPLICATIONS) *.o *~
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -rf .tmp_versions .*.cmd

