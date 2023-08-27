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
 BLK        PB6             Backlight Control
 */

int main() {

    // Configure SysTick Timer
    configure_timer(1000);

    // Initialize clock
    //clock_init();

    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable Peripheral Clocks
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE ); // (1)

    // Configure Pins (2)
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz ;
    GPIO_Init(GPIOC , &GPIO_InitStructure);

    while (1) {
        static int ledval = 0;
        // toggle led
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, ( ledval ) ? Bit_SET : Bit_RESET);
        ledval = 1 - ledval ;

        Delay (250);
    }
}
