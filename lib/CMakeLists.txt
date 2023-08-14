add_library(rcc-config STATIC rcc-config.c)
target_link_libraries(rcc-config PRIVATE stm32_common_starter)

add_library(uart-config STATIC uart-config.c)
target_link_libraries(uart-config PRIVATE stm32_common_starter)

add_library(spi-config STATIC spi-config.c)
target_link_libraries(spi-config PRIVATE stm32_common_starter)