#include "uart-config.h"

static void setup_usart_gpio(GPIO_TypeDef *gpio_typedef,
                             GPIO_InitTypeDef *gpio_init_struct,
                             uint16_t gpio_pin,
                             GPIOSpeed_TypeDef  gpio_speed,
                             GPIOMode_TypeDef gpio_mode) {
    //GPIO_StructInit(gpio_init_struct);
    gpio_init_struct->GPIO_Pin = gpio_pin;
    if (gpio_speed)
        gpio_init_struct->GPIO_Speed = gpio_speed;
    gpio_init_struct->GPIO_Mode = gpio_mode;
    GPIO_Init(gpio_typedef, gpio_init_struct);
}

static void setup_usart(USART_TypeDef *uart_x, USART_InitTypeDef * usart_init_struct, uint32_t baud_rate, uint16_t uart_mode) {
    USART_StructInit(usart_init_struct);
    usart_init_struct->USART_BaudRate = baud_rate;
    usart_init_struct->USART_Mode = uart_mode;
    USART_Init(uart_x, usart_init_struct);
    USART_Cmd(uart_x, ENABLE);
}

int uart_open(USART_TypeDef *uart_x, uint32_t baud, uint32_t flags) {
    GPIO_InitTypeDef  gpio_init_struct;
    GPIO_StructInit(&gpio_init_struct);
    USART_InitTypeDef  usart_init_struct;

    if (uart_x == USART1) {

        // Provide clock to required peripherals
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

        // Initialise tx pin
        setup_usart_gpio(GPIOA,
                         &gpio_init_struct,
                         GPIO_Pin_9,
                         GPIO_Speed_50MHz,
                         GPIO_Mode_AF_PP);

        // Initialise rx pin
        setup_usart_gpio(GPIOA,
                         &gpio_init_struct,
                         GPIO_Pin_10,
                         0,
                         GPIO_Mode_IN_FLOATING);

        // Initialise USART
        setup_usart(USART1,
                    &usart_init_struct,
                    baud,
                    USART_Mode_Rx | USART_Mode_Tx);

    } else if (uart_x == USART2) {
        // Provide clock to required peripherals
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

        // Initialise tx pin
        setup_usart_gpio(GPIOA,
                         &gpio_init_struct,
                         GPIO_Pin_2,
                         GPIO_Speed_50MHz,
                         GPIO_Mode_AF_PP);

        // Initialise rx pin
        setup_usart_gpio(GPIOA,
                         &gpio_init_struct,
                         GPIO_Pin_3,
                         0,
                         GPIO_Mode_IN_FLOATING);

        // Initialise USART
        setup_usart(USART2,
                    &usart_init_struct,
                    baud,
                    USART_Mode_Rx | USART_Mode_Tx);

    } else if (uart_x == USART3) {
        // Provide clock to required peripherals
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

        // Initialise tx pin
        setup_usart_gpio(GPIOB,
                         &gpio_init_struct,
                         GPIO_Pin_10,
                         GPIO_Speed_50MHz,
                         GPIO_Mode_AF_PP);

        // Initialise rx pin
        setup_usart_gpio(
                GPIOB,
                &gpio_init_struct,
                GPIO_Pin_11,
                0,
                GPIO_Mode_IN_FLOATING);

        // Initialise USART
        setup_usart(USART3,
                    &usart_init_struct,
                    baud,
                    USART_Mode_Rx | USART_Mode_Tx);

    }
    return 0;
}

int urt_close(USART_TypeDef *uart_x) {
    USART_Cmd(uart_x, DISABLE);

    return 0;
}

int uart_putc(int c, USART_TypeDef *uart_x){
    while(USART_GetFlagStatus(uart_x, USART_FLAG_TXE) == RESET);
    uart_x->DR = (c & 0xff);
    return 0;
}

int uart_getc(USART_TypeDef *uart_x){
    while(USART_GetFlagStatus(uart_x, USART_FLAG_RXNE) == RESET);

    return (uart_x->DR & 0xff);
}

