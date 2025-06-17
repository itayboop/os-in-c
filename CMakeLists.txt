cmake_minimum_required(VERSION 3.13)
project(x86_64_c_os CXX ASM_NASM)

set(ISO_DIR "isodir")
set(SOURCE_DIR "Sources")
set(INCLUDE_DIR "Headers")
set(OUTPUT_DIR "output")

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f elf64")

set(CMAKE_CXX_COMPILER x86_64-elf-g++)
# TODO: add optimization flag in cpp flags because it creates UB with IDT
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -g -Wall -Wextra -fno-exceptions -fno-rtti")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/linker.ld -ffreestanding -n -nostdlib -lgcc -o ${PROJECT_NAME}.bin")

file(GLOB_RECURSE SOURCES "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp" "${SOURCE_DIR}/*.c" "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.s" "${SOURCE_DIR}/*.asm" "${SOURCE_DIR}/*.nasm")

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_DIR}/boot/grub
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${ISO_DIR}/boot/${OS_BIN}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${ISO_DIR}/boot/grub
        COMMAND grub-mkrescue -o ${OUTPUT_DIR}/${PROJECT_NAME}.iso ${ISO_DIR}
        COMMAND qemu-system-x86_64 -cdrom ${OUTPUT_DIR}/${PROJECT_NAME}.iso
)
