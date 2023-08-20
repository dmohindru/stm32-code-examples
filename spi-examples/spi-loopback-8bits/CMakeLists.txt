add_executable(spi_loop_back_8b main.c)

target_sources(spi_loop_back_8b PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_spi.c)

target_link_libraries(spi_loop_back_8b PRIVATE rcc-config)
target_link_libraries(spi_loop_back_8b PRIVATE spi-config)
target_link_libraries(spi_loop_back_8b PRIVATE stm32_common_starter)