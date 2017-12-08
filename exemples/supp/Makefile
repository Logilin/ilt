ifneq (${KERNELRELEASE},)

	obj-m  = handler-01.o
	obj-m += handler-02.o

else

	export ARCH := arm
	export CROSS_COMPILE := arm-linux-

	MODULE_DIR := $(shell pwd)
	KERNEL_DIR := $(MODULE_DIR)/../../buildroot-2016.02/output/build/linux-d33d0293e245badc4ca6ede3984d8bb8ea63cb1a/

.PHONY: all
all: modules

.PHONY: modules
modules:
	${MAKE} -C ${KERNEL_DIR} SUBDIRS=${MODULE_DIR}  modules

.PHONY: clean,
clean:
	rm -f *.o *.ko *.mod.c .*.o .*.ko .*.mod.c .*.cmd *~ *.ko.unsigned
	rm -f Module.symvers Module.markers modules.order
	rm -rf .tmp_versions
endif

