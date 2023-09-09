#include "timer.h"
#include "st7735.h"
#include "rcc-config.h"
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

/*
 Pin Mapping for LCD ST7735S

 LCD        BluePill        Function
 GND        GND             Ground
 VDD        3.3V            Power
 SCL(SCK)   PB13(SCK2)      Clock for SPI2
 SDA(MOSI)  PB15(MOSI2)     Slave IN
 RST        PB9             LCD Reset
 DC         PB8             Data/Control Toggle
 CS         PB7             LCD Select
 BLK        PB6             Backlight Control (Inverted logic)
 */

int main() {

    // Configure SysTick Timer
    configure_timer(1000);

    // Initialize clock
    //clock_init();

    // Initalize st7735 lcd
    struct ST7735_Def st7735_Def = {
            .spi_x = SPI2,
            .gpio_port = GPIOB,
            .backlit = GPIO_Pin_6,
            .reset = GPIO_Pin_9,
            .chip_select = GPIO_Pin_7,
            .dc = GPIO_Pin_8,
            .width = 128,
            .height = 160
    };

    st7735_lcd_init(&st7735_Def);
    st7735_lcd_fill_screen(&st7735_Def, RED);
    st7735_draw_rectangle(&st7735_Def, 10, 10, 50, 50, BLUE);
    st7735_draw_rectangle(&st7735_Def, 60, 60, 90, 90, GREEN);

    while (1) {
        Delay(1000);
    }
}
