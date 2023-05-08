CXX=i686-elf-g++

TARGET_NAME=x86_64_c_os

SRC_DIR=src
INC_DIR=inc
BIN_DIR=bin
OUTPUT_DIR=output
ISO_DIR=isodir
OS_BIN=$(TARGET_NAME).bin

SRCS=$(shell find $(SRC_DIR) \( -name "*.cpp" -o -name "*.c++" -o -name "*.c" -o -name "*.s" \))
OBJS=$(filter %.o, $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS)) \ $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS)) \ $(patsubst $(SRC_DIR)/%.s,$(BIN_DIR)/%.o, $(SRCS)))

LDFLAGS=-T $(SRC_DIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc
CXXFLAGS=-I$(INC_DIR) -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

define src_to_object
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -c -o $@
endef

$(OUTPUT_DIR)/$(TARGET_NAME): $(OBJS)
	mkdir -p $(dir $@)
	mkdir -p $(ISO_DIR)/boot/grub
	$(CXX) $(LDFLAGS) -o $(ISO_DIR)/boot/$(OS_BIN) $^
	cp ./grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $(OUTPUT_DIR)/$(TARGET_NAME).iso $(ISO_DIR)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(call src_to_object)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(call src_to_object)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.s
	$(call src_to_object)

clean:
	rm -rf $(BIN_DIR)

cleanall: clean
	rm -rf $(ISO_DIR)
	rm -rf $(OUTPUT_DIR)
