##############################################################################
## Exemple de la formation "Temps-reel Linux et Xenomai"
##
## Christophe Blaess 2010-2020
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

APPLICATIONS:=      \
  example-VI-01    \
  example-VI-02    \
  example-VI-03    \
  example-VI-04    \
  example-VI-07    \
  example-VI-08    \
  example-VI-09    \
  example-VI-10    \
  example-VI-11    \
  example-VI-12    \


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
