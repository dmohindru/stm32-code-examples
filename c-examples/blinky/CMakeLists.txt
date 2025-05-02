add_executable(blinky main.c)

target_sources(blinky PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c)

target_link_libraries(blinky PRIVATE stm32_common_starter)

