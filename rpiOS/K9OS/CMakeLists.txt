# This file needed by CMake
# Based on http://www.valvers.com/open-software/raspberry-pi/step03-bare-metal-programming-in-c-pt3/

cmake_minimum_required( VERSION 2.8)

# language = C, ASM
project( K9OS C ASM )

# Flags
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles" )

# Executables
add_executable( k9os
		k9os.c
		k9-cstartup.c
		k9-cstubs.c
		k9-start.S )

# create binary image
add_custom_command(
	TARGET k9os POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} ./k9os${CMAKE_EXECUTABLE_SUFFIX} -O binary ./kernel.img
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Convert kernel.elf to binary kernel.img" )
	
