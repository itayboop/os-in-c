CXX=i686-elf-g++

TARGET_NAME=c_os

SRC_DIR=src
INC_DIR=inc
BIN_DIR=bin
OUTPUT_DIR=output
ISO_DIR=isodir
OS_BIN=$(TARGET_NAME).bin

SRCS=$(shell find $(SRC_DIR) \( -name "*.cpp" -o -name "*.c++" -o -name "*.c" -o -name "*.s" \))
OBJS=$(filter %.o, $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o, $(SRCS)) \ $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))\ $(patsubst $(SRC_DIR)/%.s, $(BIN_DIR)/%.o, $(SRCS)))

LDFLAGS=-T $(SRC_DIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc
CXXFLAGS=-I$(INC_DIR) -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

$(OUTPUT_DIR)/$(TARGET_NAME): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) -o $(BIN_DIR)/$(TARGET_NAME).bin $^
	$(shell cp $(BIN_DIR)/$(OS_BIN) $(ISO_DIR)/boot/$(OS_BIN))
	$(shell rm $($(BIN_DIR)/$(OS_BIN)))

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS)  $< -c -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -c -o $@

clean:
	rm -rf $(BIN_DIR)

cleanall: clean
	rm -rf $(OUTPUT_DIR)
