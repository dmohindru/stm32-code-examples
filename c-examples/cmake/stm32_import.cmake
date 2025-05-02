cmake_minimum_required(VERSION 3.12)
project(STM32_Project)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Tool path
set(TOOLROOT /usr/bin)

# Library path
set(LIBROOT /home/dhruv/opt/stm32/STM32F10x_StdPeriph_Lib_V3.6.0)

# Tools
set(CC ${TOOLROOT}/arm-none-eabi-gcc)
set(LD ${TOOLROOT}/arm-none-eabi-gcc)
set(AR ${TOOLROOT}/arm-none-eabi-ar)
set(AS ${TOOLROOT}/arm-none-eabi-as)

# Code Paths
set(DEVICE ${LIBROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x)
set(CORE ${LIBROOT}/Libraries/CMSIS/CM3/CoreSupport)
set(PERIPH ${LIBROOT}/Libraries/STM32F10x_StdPeriph_Driver)

# Search path for standard files
include_directories(${TEMPLATEROOT})

# Search path for perpheral library
include_directories(${CORE})
include_directories(${PERIPH}/src)
include_directories(${DEVICE})

# Search path for Library
include_directories(${TEMPLATEROOT}/Library/ff9/src)
include_directories(${TEMPLATEROOT}/Library/ff9/src/option)
include_directories(${TEMPLATEROOT}/Library)

# Processor specific
set(PTYPE STM32F10X_MD_VL)
set(LDSCRIPT ${TEMPLATEROOT}/stm32f100.ld)
set(STARTUP startup_stm32f10x.o system_stm32f10x.o)

# Compilation Flags
set(FULLASSERT -DUSE_FULL_ASSERT)
set(LDFLAGS -T${LDSCRIPT} -mthumb -mcpu=cortex-m3)
set(CFLAGS -mcpu=cortex-m3 -mthumb)
set(CFLAGS ${CFLAGS} -I${TEMPLATEROOT} -I${DEVICE} -I${CORE} -I${PERIPH}/inc -I.)
set(CFLAGS ${CFLAGS} -D${PTYPE} -DUSE_STDPERIPH_DRIVER ${FULLASSERT})
set(CFLAGS ${CFLAGS} -I${TEMPLATEROOT}/Library/ff9/src -I${TEMPLATEROOT}/Library)

# Source files
file(GLOB_RECURSE SOURCES "*.c")

# Build executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_options(${PROJECT_NAME} PRIVATE ${LDFLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})

# Cleanup
add_custom_target(clean_target COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeLists.txt
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/startup_stm32f*
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf)

# Debug
add_custom_target(debug COMMAND arm-none-eabi-gdb ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf)

# Include dependencies
file(GLOB DEPENDENCIES "*.d")
foreach(DEPENDENCY${DEPENDENCIES})
  include(${DEPENDENCY})
endforeach()
