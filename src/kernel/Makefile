TARGET_ASMFLAGS += -f elf
TARGET_CFLAGS += -ffreestanding -nostdlib -I.
TARGET_LIBS += -lgcc
TARGET_LINKFLAGS += -T linker.ld -nostdlib

HEADERS_C = $(wildcard *.h) \
			$(wildcard */*.h) \
			$(wildcard */*/*.h) \
			$(wildcard */*/*/*.h) \
			$(wildcard ../libs/*.h) \
			$(wildcard ../libs/*/*.h) 

SOURCES_C = $(wildcard *.c) \
			$(wildcard */*.c) \
			$(wildcard */*/*.c) \
			$(wildcard */*/*/*.c) \
			arch/i686/gen_isr.c

OBJECTS_C = $(patsubst %.c, $(BUILD_DIR)/kernel/c/%.obj, $(SOURCES_C))

HEADERS_ASM = $(wildcard *.inc) \
			  $(wildcard */*.inc) \
			  $(wildcard */*/*.inc) \
			  $(wildcard */*/*/*.inc) \
			  arch/i686/gen_isr.inc

SOURCES_ASM = $(wildcard *.asm) \
			  $(wildcard */*.asm) \
			  $(wildcard */*/*.asm) \
			  $(wildcard */*/*/*.asm)


OBJECTS_ASM = $(patsubst %.asm, $(BUILD_DIR)/kernel/asm/%.obj, $(SOURCES_ASM))

# i love rejanking this cuz yes (its 4am fuck off)

.PHONY: all kernel clean always

all: kernel

kernel: $(BUILD_DIR)/nanite.bin

$(BUILD_DIR)/nanite.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	@$(TARGET_LD) $(TARGET_LINKFLAGS) -Wl,-Map=$(BUILD_DIR)/kernel.map -o $@ $^ $(TARGET_LIBS)
	@echo "--> Created:  nanite.bin"

$(BUILD_DIR)/kernel/c/%.obj: %.c $(HEADERS_C)
	@mkdir -p $(@D)
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<
	@echo "--> Compiled: " $<

$(BUILD_DIR)/kernel/asm/%.obj: %.asm $(HEADERS_ASM)
	@mkdir -p $(@D)
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) -o $@ $<
	@echo "--> Compiled: " $<

arch/i686/gen_isr.c arch/i686/gen_isr.inc:
	@$(SOURCE_DIR)/build_scripts/genISR.sh $@
	@echo "--> Compiled: ISR Gen Files"

clean:
	rm -f $(BUILD_DIR)/nanite.bin