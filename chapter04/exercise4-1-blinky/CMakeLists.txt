add_executable(ch04_blink main.c)

target_sources(ch04_blink PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c)

target_link_libraries(ch04_blink PRIVATE stm32_common_starter)

