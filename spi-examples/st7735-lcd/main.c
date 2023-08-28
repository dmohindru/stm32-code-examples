#include "timer.h"
#include "ST7735.h"
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


    ST7735_init();
    while (1) {
        ST7735_fillScreen(RED);
        Delay(1000);

        ST7735_fillScreen(GREEN);
        Delay(1000);

        ST7735_fillScreen(BLUE);
        Delay(1000);

        ST7735_fillScreen(YELLOW);
        Delay(1000);

        ST7735_fillScreen(WHITE);
        Delay(1000);

        ST7735_fillScreen(BLACK);
        Delay(1000);

        ST7735_fillScreen(CYAN);
        Delay(1000);

        ST7735_fillScreen(MAGENTA);
        Delay(1000);

    }
}
