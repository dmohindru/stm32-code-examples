add_executable(st7735_lcd main.c ST7735.c)

target_sources(st7735_lcd PRIVATE
        ${PERIPH}/src/stm32f10x_gpio.c
        ${PERIPH}/src/stm32f10x_rcc.c
        ${PERIPH}/src/stm32f10x_spi.c)

target_link_libraries(st7735_lcd PRIVATE rcc-config)
target_link_libraries(st7735_lcd PRIVATE spi-config)
target_link_libraries(st7735_lcd PRIVATE timer)
target_link_libraries(st7735_lcd PRIVATE stm32_common_starter)

# Temp stuff
#add_executable(st7735_lcd main.c)
#
#target_sources(st7735_lcd PRIVATE
#        ${PERIPH}/src/stm32f10x_gpio.c
#        ${PERIPH}/src/stm32f10x_rcc.c)
#
#target_link_libraries(st7735_lcd PRIVATE rcc-config)
#target_link_libraries(st7735_lcd PRIVATE timer)
#target_link_libraries(st7735_lcd PRIVATE stm32_common_starter)