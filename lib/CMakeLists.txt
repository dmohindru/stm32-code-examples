add_library(rcc-config STATIC rcc-config.c)
target_link_libraries(rcc-config PRIVATE stm32_common_starter)

add_library(uart-config STATIC uart-config.c)
target_link_libraries(uart-config PRIVATE stm32_common_starter)