add_executable(ch04_blink_button_pull_up main.c)

target_sources(ch04_blink_button_pull_up PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c)

target_link_libraries(ch04_blink_button_pull_up PRIVATE stm32_common_starter)

