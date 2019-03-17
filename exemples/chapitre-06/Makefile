##############################################################################
## Exemple de la formation "Temps-reel Linux et Xenomai"
##
## Christophe Blaess 2010-2018
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

APPLICATIONS:=      \
  exemple-VI-01    \
  exemple-VI-02    \
  exemple-VI-03    \
  exemple-VI-04    \
  exemple-VI-07    \
  exemple-VI-08    \
  exemple-VI-09    \
  exemple-VI-10    \
  exemple-VI-11    \
  exemple-VI-12    \


ifneq (${KERNELRELEASE},)

  obj-m += exemple-VI-05.o
  obj-m += exemple-VI-06.o


else

CFLAGS=-Wall -g -pthread
LDFLAGS=-pthread
LOADLIBES=-lrt
CC = ${CROSS_COMPILE}gcc
AS = ${CROSS_COMPILE}as
LD = ${CROSS_COMPILE}gcc

	CROSS_COMPILE ?=
	ARCH          ?=
	KERNEL_DIR    ?= /lib/modules/$(shell uname -r)/build
	MODULE_DIR    := $(shell pwd)

.PHONY: all
all: ${APPLICATIONS}

.PHONY: modules
modules:
	${MAKE} arch=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C ${KERNEL_DIR} SUBDIRS=${MODULE_DIR}  modules

.PHONY: clean
clean:
	rm -f ${APPLICATIONS} *.o *~
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -rf .tmp_versions .*.cmd

endif
