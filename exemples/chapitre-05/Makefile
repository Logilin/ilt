
APPLICATIONS:=              \
	exemple-01          \
	exemple-02          \
	exemple-03          \
	exemple-04          \
	exemple-07          \
	exemple-08          \
	exemple-09          \
	exemple-10          \
	exemple-11          \
	exemple-12          \


ifneq (${KERNELRELEASE},)

	# Exemples pour Raspberry Pi
	obj-m += exemple-05.o
	obj-m += exemple-06.o


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

clean::
	rm -f ${APPLICATIONS} *.o *~
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -rf .tmp_versions .*.cmd

endif
