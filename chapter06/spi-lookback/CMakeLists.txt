add_executable(spi_loop_back main.c)

target_sources(spi_loop_back PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_spi.c)

target_link_libraries(spi_loop_back PRIVATE rcc-config)
target_link_libraries(spi_loop_back PRIVATE spi-config)
target_link_libraries(spi_loop_back PRIVATE stm32_common_starter)