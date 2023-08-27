#include "timer.h"

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay !=0);
}

void SysTick_Handler(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}

void configure_timer(uint32_t divider) {
    if (SysTick_Config(SystemCoreClock / divider)) {
        while (1);
    }
}