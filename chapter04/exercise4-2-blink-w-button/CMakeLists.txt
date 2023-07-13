add_executable(ch04_blink_button main.c)

target_sources(ch04_blink_button PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c)

target_link_libraries(ch04_blink_button PRIVATE stm32_common_starter)

