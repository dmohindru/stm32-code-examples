#include "uart.h"
#include <string.h>

void Delay(uint32_t nTime);

char string_to_send[] = "Hello World!\n\r";

void CLOCK_Init(void)
{

    RCC_TypeDef * pRCC;
    pRCC = RCC;
    RCC_ClocksTypeDef clocks;

    uint32_t cpCFGR;

    uint32_t mask;

    //Setting HSI as system clock
    cpCFGR = pRCC->CFGR;


    // clear the SW1 SW0: Clock Source HSI
    mask = ~((uint32_t)0b011);

    cpCFGR &= mask;

    pRCC->CFGR = cpCFGR;

    // wait till SWS is 00, that is the clock source is HSI
    while(1)
    {
        cpCFGR = pRCC->CFGR>>2;
        if((~(cpCFGR) & (uint32_t)0b010) == (uint32_t)0b010) break;
    }


    /* Since the UART2 is connected to APB1 lets configure
     * the prescaler in a known value, lets say 1
     * */
    //change the preescaler of APB1 from 4 to 1

    cpCFGR = pRCC->CFGR;

    mask = ~((uint32_t)0x00001C00); // RCC_CFGR_PPRE1

    cpCFGR &= mask;

    pRCC->CFGR = cpCFGR;

}

int main(void) {

    CLOCK_Init();
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