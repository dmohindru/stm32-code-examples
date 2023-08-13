#include "rcc-config.h"
#include <stm32f10x_rcc.h>

void clock_init(void){
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
