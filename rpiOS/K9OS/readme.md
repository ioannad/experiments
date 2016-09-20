# K9 OS

## Hello, World! 
This kernel makes the OK (ACT) LED blink.

### Dependency
arm-none-eabi-gcc (Debian package gcc-arm-none-eabi)

### Usage
`build.sh` creates `kernel.img`. Copy this file, along with the two firmware files from [the Raspberry Pi repository](https://github.com/raspberrypi/firmware) or from this folder: `bootcode.bin` and `start.elf` in a FAT-formatted SD card. Insert SD card to a Raspberry Pi B, power up and watch the LED blink.
