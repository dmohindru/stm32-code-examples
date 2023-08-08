add_executable(uart_text_command main.c main.h)

target_sources(uart_text_command PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_usart.c)

target_link_libraries(uart_text_command PRIVATE stm32_common_starter)