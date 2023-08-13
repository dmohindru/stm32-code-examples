#include "uart-config.h"
#include "rcc-config.h"
#include <string.h>

void Delay(uint32_t nTime);

char string_to_send[] = "Hello World!\n\r";

int main(void) {

    clock_init();
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE ); // (1)

    // Configure Pins (2)
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz ;
    GPIO_Init(GPIOC , &GPIO_InitStructure);

    uart_open(USART2, 115200, 0);

    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }

    while (1) {
        for (int i = 0; i < strlen(string_to_send); i++) {
            uart_putc(string_to_send[i], USART2);
        }


        static int ledval = 0;
        // toggle led
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, ( ledval ) ? Bit_SET : Bit_RESET);
        ledval = 1 - ledval ;

        Delay(500);

    }
}

// Timer code
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime) {
    TimingDelay = nTime;
    while (TimingDelay != 0);
}

void SysTick_Handler(void) {
    if (TimingDelay != 0x00)
        TimingDelay--;
}