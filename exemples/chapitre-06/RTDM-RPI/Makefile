
EXTRA_CFLAGS := -I /usr/local/src/xenomai-2.6.2.1/RPI/usr/xenomai/include/

ifneq (${KERNELRELEASE},)
	obj-m += irq-gpio-rtdm.o
	obj-m += oscillateur-gpio-rtdm.o

else
	ARCH ?= arm
	CROSS_COMPILE ?= /usr/local/cross/rpi/bin/arm-linux-
	KERNEL_DIR = /usr/local/src/linux-3.5.7-xenomai
	MODULE_DIR := $(shell pwd)
	CFLAGS := -Wall -g 

.PHONY: all
all:: modules

.PHONY: modules
modules:
	${MAKE} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C ${KERNEL_DIR} SUBDIRS=${MODULE_DIR}  modules

XENOCONFIG=/usr/local/src/xenomai-2.6.2.1/RPI/usr/xenomai/bin/xeno-config

.PHONY: clean
clean::
	rm -f  *.o  .*.o  .*.o.* *.ko  .*.ko  *.mod.* .*.mod.* .*.cmd *~
	rm -f Module.symvers Module.markers modules.order 
	rm -rf .tmp_versions
endif
