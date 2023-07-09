cmake_minimum_required(VERSION 3.0)
project(blinky)

set(ELF ${PROJECT_NAME}.elf)

enable_language(ASM)
# Get path to STM32 Library from environment variable STM32_LIBROOT
# If variable not found exit with error
# otherwise set various variable as below

set(STARTUP_FILE "startup_stm32f10x.c")
set(LIBROOT "/home/dhruv/opt/stm32/STM32F10x_StdPeriph_Lib_V3.6.0")
set(DEVICE "${LIBROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x")
set(CORE "${LIBROOT}/Libraries/CMSIS/CM3/CoreSupport")
set(PERIPH "${LIBROOT}/Libraries/STM32F10x_StdPeriph_Driver")

# Compile options
#set(FULLASSERT "USE_FULL_ASSERT")
#set(THUMB "thumb")

# TODO change PTYPE to appropriate value
set(PTYPE "STM32F10X_MD_VL")
set(LDSCRIPT "${CMAKE_CURRENT_LIST_DIR}/stm32f100.ld")

include_directories("${DEVICE}" "${CORE}" "${PERIPH}/inc" ".")

#message("---- sdk info ----")
#message("LIBROOT ${LIBROOT}")
#message("DEVICE ${DEVICE}")
#message("CORE ${CORE}")
#message("PERIPH ${PERIPH}")
#message("PTYPE ${PTYPE}")
#message("LDSCRIPT ${LDSCRIPT}")
#message("${CMAKE_CURRENT_LIST_FILE}")
#
#message("---include directories---")
#
#get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(include_dir ${include_dirs})
#    message("Include directory: ${include_dir}")
#endforeach()

# Common Interface target for compiler definitions, compiler options and linker options
add_library(stm32_common INTERFACE)

target_compile_definitions(stm32_common INTERFACE
        "${PTYPE}"
        USE_STDPERIPH_DRIVER
        FULLASSERT)

target_compile_options(stm32_common INTERFACE
        -mthumb
        -mcpu=cortex-m3)

target_link_options(stm32_common INTERFACE
        -T${LDSCRIPT}
        -mthumb
        -mcpu=cortex-m3)

# Common library for starter code
add_library(stm32_common_starter STATIC)

target_sources(stm32_common_starter PRIVATE
        startup_stm32f10x.c
        ${DEVICE}/system_stm32f10x.c)

target_link_libraries(stm32_common_starter stm32_common)

add_subdirectory(blinky)

