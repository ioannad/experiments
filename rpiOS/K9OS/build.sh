#!/usr/bin/bash

arm-none-eabi-gcc -O0 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,-verbose k9os.c k9-cstubs.c k9-cstartup.c k9-start.S -o kernel.elf

arm-none-eabi-objcopy kernel.elf -O binary kernel.img

