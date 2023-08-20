add_executable(uart_echo_second main.c)

target_sources(uart_echo_second PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_usart.c)

target_link_libraries(uart_echo_second PRIVATE rcc-config)
target_link_libraries(uart_echo_second PRIVATE uart-config)
target_link_libraries(uart_echo_second PRIVATE stm32_common_starter)