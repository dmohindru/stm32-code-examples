#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>

int uart_open(USART_TypeDef *uart_x, uint32_t baud, uint32_t flags);
int urt_close(USART_TypeDef *uart_x);
int uart_putc(int c, USART_TypeDef *uart_x);
int uart_getc(USART_TypeDef *uart_x);