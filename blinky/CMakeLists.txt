add_executable(blinky main.c)

target_compile_definitions(blinky PRIVATE
        "${PTYPE}"
        USE_STDPERIPH_DRIVER
        FULLASSERT)

target_sources(blinky PRIVATE
        ../startup_stm32f10x.c
        ${DEVICE}/system_stm32f10x.c
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c)

target_compile_options(blinky PRIVATE
        -mthumb
        -mcpu=cortex-m3)

target_link_options(blinky PRIVATE
        -T${LDSCRIPT}
        -mthumb
        -mcpu=cortex-m3)

