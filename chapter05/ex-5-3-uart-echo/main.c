#include "uart-config.h"
#include <string.h>

void Delay(uint32_t nTime);



int main(void) {

    uart_open(USART1, 9600, 0);

    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }

    while (1) {
        int ch = uart_getc(USART1);
        uart_putc(ch, USART1);
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