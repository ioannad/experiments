#!/usr/bin/env bash

arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles k9os.c -o kernel.elf

arm-none-eabi-objcopy kernel.elf -O binary kernel.img

