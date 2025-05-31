include build_scripts/config.mk

.PHONY: all floppy_image kernel bootloader clean always tools_fat

all: floppy_image tools_fat

include build_scripts/toolchain.mk
# oldnum = cat version
# newnum = expr $(oldnum) + 1
# export oldnum
# export newnum

#
# Floppy image
#
floppy_image: $(BUILD_DIR)/main_floppy.img

$(BUILD_DIR)/main_floppy.img: bootloader kernel
	dd if=/dev/zero of=$(BUILD_DIR)/main_floppy.img bs=512 count=2880
	mkfs.fat -F 12 -n "NANITE" $(BUILD_DIR)/main_floppy.img
	dd if=$(BUILD_DIR)/stage1.bin of=$(BUILD_DIR)/main_floppy.img conv=notrunc
	mmd -i $(BUILD_DIR)/main_floppy.img "::boot"
	mmd -i $(BUILD_DIR)/main_floppy.img "::misc"
	mcopy -v -i $(BUILD_DIR)/main_floppy.img $(BUILD_DIR)/kernel.bin "::boot"
	mcopy -i $(BUILD_DIR)/main_floppy.img $(BUILD_DIR)/nboot.bin "::nboot.bin"
	mcopy -v -i $(BUILD_DIR)/main_floppy.img kparams "::boot"
	mcopy -v -i $(BUILD_DIR)/main_floppy.img test "::boot"

#
# Bootloader
#
#
bootloader: stage1 stage2

stage1: $(BUILD_DIR)/stage1.bin

$(BUILD_DIR)/stage1.bin: always
	$(MAKE) -C src/bootloader/stage1 BUILD_DIR=$(abspath $(BUILD_DIR))

stage2: $(BUILD_DIR)/stage2.bin

$(BUILD_DIR)/stage2.bin: always
	$(MAKE) -C src/bootloader/stage2 BUILD_DIR=$(abspath $(BUILD_DIR))


#
# Kernel
#
kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: always
	$(MAKE) -C src/kernel BUILD_DIR=$(abspath $(BUILD_DIR))

#
# Tools
#
tools_fat: $(BUILD_DIR)/tools/fat
$(BUILD_DIR)/tools/fat: always tools/fat/fat.c
	mkdir -p $(BUILD_DIR)/tools
	$(CC) -g -o $(BUILD_DIR)/tools/fat tools/fat/fat.c

#
# Always
#
always:  
	mkdir -p $(BUILD_DIR)
#	echo Version $(oldnum)
#	sed -i '9i s/#define VERSION "RD-//#define VERSION "RD-$(newnum)/"' src/libs/version.h



#
# Clean
#
clean:
	$(MAKE) -C src/bootloader/stage1 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	$(MAKE) -C src/bootloader/stage2 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	$(MAKE) -C src/kernel BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	rm -rf $(BUILD_DIR)/*
	rm -rf src/bootloader/stage2/*.err
