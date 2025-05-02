add_executable(uart_processor main.c uart-processor.h)

add_library(uart_dummy_processor STATIC dummy-processor.c uart-processor.h)
target_link_libraries(uart_dummy_processor PRIVATE stm32_common_starter)

add_library(uart_ascii_processor STATIC ascii-processor.c uart-processor.h)
target_link_libraries(uart_ascii_processor PRIVATE stm32_common_starter)

target_sources(uart_processor PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_usart.c)

target_link_libraries(uart_processor PRIVATE rcc-config)
target_link_libraries(uart_processor PRIVATE uart-config)
target_link_libraries(uart_processor PRIVATE uart_ascii_processor)
target_link_libraries(uart_processor PRIVATE stm32_common_starter)