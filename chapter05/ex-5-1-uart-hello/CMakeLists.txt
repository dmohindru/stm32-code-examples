add_executable(uart_hello main.c)

include_directories("../uart-lib")

target_sources(uart_hello PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_usart.c)

target_link_libraries(uart_hello PRIVATE uart-lib)
target_link_libraries(uart_hello PRIVATE stm32_common_starter)