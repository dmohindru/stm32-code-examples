
cmake_minimum_required(VERSION 3.0)
project(blinky)

set(ELF ${PROJECT_NAME}.elf)

enable_language(ASM)
set(STARTUP_FILE "startup_stm32f10x.c")
set(LIBROOT "/home/dhruv/opt/stm32/STM32F10x_StdPeriph_Lib_V3.6.0")
set (DEVICE "${LIBROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x")
set(CORE "${LIBROOT}/Libraries/CMSIS/CM3/CoreSupport")
set(PERIPH "${LIBROOT}/Libraries/STM32F10x_StdPeriph_Driver")

# Compile options
set(FULLASSERT "USE_FULL_ASSERT")
set(THUMB "thumb")

# TODO change PTYPE to appropriate value
set(PTYPE "STM32F10X_MD_VL")
set(LDSCRIPT "../stm32f100.ld")

include_directories("${DEVICE}" "${CORE}" "${PERIPH}/inc" ".")

message("---- sdk info ----")
message("LIBROOT ${LIBROOT}")
message("DEVICE ${DEVICE}")
message("CORE ${CORE}")
message("PERIPH ${PERIPH}")
message("PTYPE ${PTYPE}")
message("LDSCRIPT ${LDSCRIPT}")

message("---include directories---")

get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(include_dir ${include_dirs})
    message("Include directory: ${include_dir}")
endforeach()

add_subdirectory(blinky)

