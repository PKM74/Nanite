export CFLAGS = -std=c99 -g
export ASM = nasm
export ASMFLAGS = 
export CC = gcc
export CXX = g++
export LD = gcc
export LINKFLAGS = 
export LIBS = 

export TARGET = i686-elf
export TARGET_ASM = nasm
export TARGET_ASMFLAGS = 
export TARGET_CFLAGS = -std=c99 -g
export TARGET_CC = $(TARGET)-gcc
export TARGET_CXX = $(TARGET)-g++
export TARGET_LD = $(TARGET)-gcc
export TARGET_LINKFLAGS = 
export TARGET_LIBS = 

export BUILD_DIR = $(abspath build)
export SOURCE_DIR = $(abspath .)

# i hate making make files...

BINUTILS_VERSION = 2.43.1
BINUTILS_URL = https://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VERSION).tar.gz
GCC_VERSION = 14.2.0
GCC_URL = https://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VERSION)/gcc-$(GCC_VERSION).tar.gz