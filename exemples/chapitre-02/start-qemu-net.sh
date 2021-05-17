#!/bin/sh
(
BINARIES_DIR="${0%/*}/"
cd ${BINARIES_DIR}

if [ "${1}" = "serial-only" ]; then
    EXTRA_ARGS='-nographic'
else
    EXTRA_ARGS='-serial stdio'
fi

export PATH="../host/bin:${PATH}"
exec qemu-system-arm -M vexpress-a9 -smp 1 -m 256 -kernel zImage -dtb vexpress-v2p-ca9.dtb -drive file=rootfs.ext2,if=sd,format=raw -append "console=ttyAMA0,115200 rootwait root=/dev/mmcblk0"  -net nic,model=lan9118 -net tap,script="qemu-ifup" ${EXTRA_ARGS}
)
