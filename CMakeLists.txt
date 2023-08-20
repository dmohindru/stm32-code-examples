cmake_minimum_required(VERSION 3.0)
project(discovering_stm32)

enable_language(ASM)

if (NOT DEFINED ENV{STM32_LIBROOT})
    message(FATAL_ERROR "STM32_LIBROOT environment need to be define to library root")
endif ()


set(STARTUP_FILE "startup_stm32f10x.c")
set(LIBROOT $ENV{STM32_LIBROOT})
set(DEVICE "${LIBROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x")
set(CORE "${LIBROOT}/Libraries/CMSIS/CM3/CoreSupport")
set(PERIPH "${LIBROOT}/Libraries/STM32F10x_StdPeriph_Driver")

# TODO change PTYPE to appropriate value
set(PTYPE "STM32F10X_MD_VL")
set(LDSCRIPT "${CMAKE_CURRENT_LIST_DIR}/stm32f100.ld")

include_directories("${DEVICE}" "${CORE}" "${PERIPH}/inc" "." "inc")

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

# All code examples in this project
add_subdirectory(blinky)
add_subdirectory(hello-world)
add_subdirectory(chapter04)
add_subdirectory(chapter05)
add_subdirectory(spi-examples)
add_subdirectory(lib)