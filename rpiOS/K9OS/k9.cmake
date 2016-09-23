# CMake toolchain for cross-compiling for Raspberry Pi bare metal
# Adapted from http://www.valvers.com/open-software/raspberry-pi/step03-bare-metal-programming-in-c-pt3/

include(CMakeForceCompiler)

# use from same folder with:
# cmake -DCMAKE_TOOLCHAIN_FILE=./k9.cmake ./

# "Generic" for embedded systems
set( CMAKE_SYSTEM_NAME      Generic )
set( CMAKE_SYSTEM_PROCESSOR BCM2835 )

# toolchain prefix
set( CROSS_COMPILE arm-none-eabi- )

# specify cross compiler
CMAKE_FORCE_C_COMPILER( ${CROSS_COMPILE}gcc GNU )

# objcopy setting
set( CMAKE_OBJCOPY ${CROSS_COMPILE}objcopy
    CACHE FILEPATH "The toolchain objcopy command " FORCE )

# CMake flags
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=vfp" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=hard" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv6zk" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mtune=arm1176jzf-s" )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" )
set( CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" )
