##############################################################################
## Exemple de la formation "Temps-reel sous Linux"
##
## Christophe Blaess 2010-2025
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

APPLICATIONS:=     \
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


ifneq ($(KERNELRELEASE),)

  obj-m += example-VI-05.o
  obj-m += example-VI-06.o


else

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

.PHONY: modules
modules:
	$(MAKE) arch=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(MODULE_DIR)  modules

.PHONY: clean
clean:
	rm -f $(APPLICATIONS) *.o *~
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -rf .tmp_versions .*.cmd

endif
