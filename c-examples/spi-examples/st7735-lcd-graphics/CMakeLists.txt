add_executable(st7735_lcd_graphics main.c)

target_sources(st7735_lcd_graphics PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_spi.c)

target_link_libraries(st7735_lcd_graphics PRIVATE st7735)
target_link_libraries(st7735_lcd_graphics PRIVATE rcc-config)
target_link_libraries(st7735_lcd_graphics PRIVATE spi-config)
target_link_libraries(st7735_lcd_graphics PRIVATE timer)
target_link_libraries(st7735_lcd_graphics PRIVATE stm32_common_starter)