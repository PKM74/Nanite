
TOOLCHAIN_PREFIX = $(abspath toolchain/$(TARGET))
export PATH := $(TOOLCHAIN_PREFIX)/bin:$(PATH)

toolchain: toolchain_binutils toolchain_gcc

BINUTILS_SRC = toolchain/binutils-$(BINUTILS_VERSION)
BINUTILS_BUILD = toolchain/binutils-build-$(BINUTILS_VERSION)

toolchain_binutils: $(BINUTILS_SRC).tar.gz

	cd toolchain && tar -xf binutils-$(BINUTILS_VERSION).tar.gz
	mkdir -p $(BINUTILS_BUILD)
	cd $(BINUTILS_BUILD) && CFLAGS = ASM = ASMFLAGS = CC = CXX = LD = LINKFLAGS = LIBS =  ../binutils-$(BINUTILS_VERSION)/configure \
		--prefix="$(TOOLCHAIN_PREFIX)"	\
		--target=$(TARGET)				\
		--with-sysroot					\
		--disable-nls					\
		--disable-werror
	$(MAKE) -j10 -C $(BINUTILS_BUILD)
	$(MAKE) -C $(BINUTILS_BUILD) install

$(BINUTILS_SRC).tar.gz:
	mkdir -p toolchain
	cd toolchain && wget $(BINUTILS_URL)


GCC_SRC = toolchain/gcc-$(GCC_VERSION)
GCC_BUILD = toolchain/gcc-build-$(GCC_VERSION)

toolchain_gcc: toolchain_binutils $(GCC_SRC).tar.gz
	cd toolchain && tar -xf gcc-$(GCC_VERSION).tar.gz
	mkdir -p $(GCC_BUILD)
	cd $(GCC_BUILD) && CFLAGS = ASM = ASMFLAGS = CC = CXX = LD = LINKFLAGS = LIBS = ../gcc-$(GCC_VERSION)/configure \
		--prefix="$(TOOLCHAIN_PREFIX)"	\
		--target=$(TARGET)				\
		--disable-nls					\
		--enable-languages=c,c++		\
		--without-headers
	$(MAKE) -j10 -C $(GCC_BUILD) all-gcc all-target-libgcc
	$(MAKE) -C $(GCC_BUILD) install-gcc install-target-libgcc

$(GCC_SRC).tar.gz:
	mkdir -p toolchain
	cd toolchain && wget $(GCC_URL)


# CLEAN
clean-toolchain:
	rm -rf $(GCC_BUILD) $(GCC_SRC) $(BINUTILS_BUILD) $(BINUTILS_SRC)

clean-toolchain-all:
	rm -rf toolchain/*


.PHONY: toolchain toolchain_gcc toolchain_binutils

