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


    //ST7735_init();
    // Initalize st7735 lcd
    struct ST7735_Def st7735_Def;
    st7735_def_init(&st7735_Def,
                    SPI2,
                    GPIOB,
                    GPIO_Pin_6,
                    GPIO_Pin_9,
                    GPIO_Pin_7,
                    GPIO_Pin_8,
                    128,
                    160);
    st7735_lcd_init(&st7735_Def);

    while (1) {
        st7735_lcd_fill_screen(&st7735_Def, RED);
        //ST7735_fillScreen(RED);
        Delay(1000);

        st7735_lcd_fill_screen(&st7735_Def, GREEN);
        //ST7735_fillScreen(BLUE);
        Delay(1000);
//
        st7735_lcd_fill_screen(&st7735_Def, BLUE);
        Delay(1000);

        st7735_lcd_fill_screen(&st7735_Def, YELLOW);
        Delay(1000);

        st7735_lcd_fill_screen(&st7735_Def, WHITE);
        Delay(1000);

        st7735_lcd_fill_screen(&st7735_Def, BLACK);
        Delay(1000);

        st7735_lcd_fill_screen(&st7735_Def, CYAN);
        Delay(1000);

        st7735_lcd_fill_screen(&st7735_Def, MAGENTA);
        Delay(1000);

    }
}
