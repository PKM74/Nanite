include build_scripts/config.mk

.PHONY: all floppy_image kernel bootloader clean always tools_fat

all: image

include build_scripts/toolchain.mk
# oldnum = cat version
# newnum = expr $(oldnum) + 1
# export oldnum
# export newnum

#
# Image
#
image: $(BUILD_DIR)/main.img

$(BUILD_DIR)/main.img: bootloader kernel
	dd if=/dev/zero of=$(BUILD_DIR)/main.img bs=512 count=20000
	mkfs.ext2 $(BUILD_DIR)/main.img
	e2mkdir $(BUILD_DIR)/main.img:boot
	e2mkdir $(BUILD_DIR)/main.img:misc
	e2mkdir $(BUILD_DIR)/main.img:misc/src
	e2mkdir $(BUILD_DIR)/main.img:boot/grub
#	e2cp -v -s src/ -d $(BUILD_DIR)/main.img:misc/src really, really, really slow...
	e2cp grub/* $(BUILD_DIR)/main.img:boot/grub
	mkdir -p $(BUILD_DIR)/mnt

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
