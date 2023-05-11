# cmake_minimum_required(VERSION 3.10)
# project(C_OS)

# include_directories(Headers)
# file(GLOB c_os_sources "Sources/*.c" "Sources/*.cpp" "Headers/*.h" "Headers/*.hpp")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -O2 -Wall -Wextra -ffreestanding")
# add_executable(C_OS ${c_os_sources})

cmake_minimum_required(VERSION 3.13)
project(C_OS C ASM)

# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -ffreestanding -O2")
set(LDFLAGS "-T ${LINKER_SCRIPT} -ffreestanding -O2 -nostdlib -lgcc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -O2 -Wall -Wextra -std=gnu99")

set(ISO_DIR "isodir")
set(SOURCE_DIR "Sources")
set(INCLUDE_DIR "Headers")
set(OUTPUT_DIR "output")
set(OS_BIN "${PROJECT_NAME}.bin")
set(LINKER_SCRIPT "linker.ld")

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.c" "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.s" "${SOURCE_DIR}/*.asm")

add_executable(${PROJECT_NAME} ${SRCS})
target_link_options(${PROJECT_NAME} PRIVATE ${LDFLAGS})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_DIR}/boot/grub
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${ISO_DIR}/boot/${OS_BIN}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${ISO_DIR}/boot/grub
    COMMAND grub-mkrescue -o ${OUTPUT_DIR}/${PROJECT_NAME}.iso ${ISO_DIR}
)

add_custom_target(run
    COMMAND qemu-system-i386 -cdrom ${OUTPUT_DIR}/${PROJECT_NAME}.iso
)

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BIN_DIR} ${ISO_DIR} ${OUTPUT_DIR}
)

add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BIN_DIR}
)
