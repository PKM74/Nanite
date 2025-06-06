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
	mmd -i $(BUILD_DIR)/main_floppy.img "::boot"
	mmd -i $(BUILD_DIR)/main_floppy.img "::misc"
	mmd -i $(BUILD_DIR)/main_floppy.img "::misc/src"
	mcopy -s -i $(BUILD_DIR)/main_floppy.img src/* "::misc/src"

#
# Kernel
#
kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: always
	$(MAKE) -C src/kernel BUILD_DIR=$(abspath $(BUILD_DIR))

#
# Always
#
always:  
	mkdir -p $(BUILD_DIR)



#
# Clean
#
clean:
	$(MAKE) -C src/kernel BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	rm -rf $(BUILD_DIR)/*
	rm -rf src/bootloader/stage2/*.err
