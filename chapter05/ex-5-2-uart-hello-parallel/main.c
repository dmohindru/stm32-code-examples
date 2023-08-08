#include "uart.h"
#include <string.h>

void Delay(uint32_t nTime);

char string_to_send[] = "Hello from UART1\n\r";
char second_string_to_send[] = "Hello from UART2\n\r";


int main(void) {

    uart_open(USART1, 9600, 0);
    uart_open(USART2, 19200, 0);

    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }

    while (1) {
        for (int i = 0; i < strlen(string_to_send); i++) {
            uart_putc(string_to_send[i], USART1);
        }

        for (int i = 0; i < strlen(second_string_to_send); i++) {
            uart_putc(second_string_to_send[i], USART2);
        }

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