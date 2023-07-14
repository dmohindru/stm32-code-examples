add_executable(ch04_blink_button_pull_down main.c)

target_sources(ch04_blink_button_pull_down PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c)

target_link_libraries(ch04_blink_button_pull_down PRIVATE stm32_common_starter)

