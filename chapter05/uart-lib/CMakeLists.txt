add_library(uart-lib STATIC uart.c uart.h)

target_link_libraries(uart-lib PRIVATE stm32_common_starter)