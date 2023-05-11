cmake_minimum_required(VERSION 3.13)
project(C_OS C ASM)

set(CMAKE_C_COMPILER i686-elf-g++)
set(CMAKE_ASM_COMPILER i686-elf-g++)

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -ffreestanding -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -v")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/linker.ld -ffreestanding -O2 -nostdlib -lgcc")

set(ISO_DIR "isodir")
set(SOURCE_DIR "Sources")
set(INCLUDE_DIR "Headers")
set(OUTPUT_DIR "output")
set(OS_BIN "${PROJECT_NAME}.bin")

file(GLOB_RECURSE SOURCES "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp" "${SOURCE_DIR}/*.c" "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.s" "${SOURCE_DIR}/*.asm")

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_DIR}/boot/grub
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${ISO_DIR}/boot/${OS_BIN}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${ISO_DIR}/boot/grub
    COMMAND grub-mkrescue -o ${OUTPUT_DIR}/${PROJECT_NAME}.iso ${ISO_DIR}
)

add_custom_target(run
    COMMAND qemu-system-i386 -cdrom ${OUTPUT_DIR}/${PROJECT_NAME}.iso
)
