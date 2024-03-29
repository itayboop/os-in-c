CC=i686-elf-gcc

TARGET_NAME=x86_64_c_os

SRC_DIR=src
INC_DIR=inc
BIN_DIR=bin
OUTPUT_DIR=output
ISO_DIR=isodir

LINKER_SCRIPT=$(SRC_DIR)/linker.ld
OS_BIN=$(TARGET_NAME).bin

SRCS=$(shell find $(SRC_DIR) \( -name "*.c" -o -name "*.s" \))
OBJS=$(filter %.o, $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS)) \ $(patsubst $(SRC_DIR)/%.s,$(BIN_DIR)/%.o, $(SRCS)))

LDFLAGS=-T $(LINKER_SCRIPT) -ffreestanding -O2 -nostdlib -lgcc
CFLAGS=-I$(INC_DIR) -std=gnu99 -O2 -Wall -Wextra -ffreestanding

define src_to_object
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -c -o $@
endef

$(OUTPUT_DIR)/$(TARGET_NAME): $(OBJS)
	mkdir -p $(dir $@)
	mkdir -p $(ISO_DIR)/boot/grub
	$(CC) $(LDFLAGS) -o $(ISO_DIR)/boot/$(OS_BIN) $^
	cp ./grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $(OUTPUT_DIR)/$(TARGET_NAME).iso $(ISO_DIR)
	@qemu-system-i386 -cdrom $(OUTPUT_DIR)/$(TARGET_NAME).iso


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(call src_to_object)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.s
	$(call src_to_object)

run:
	@qemu-system-i386 -cdrom $(OUTPUT_DIR)/$(TARGET_NAME).iso

clean:
	rm -rf $(BIN_DIR)

cleanall: clean
	rm -rf $(ISO_DIR)
	rm -rf $(OUTPUT_DIR)
