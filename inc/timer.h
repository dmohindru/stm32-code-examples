//
// Created by dhruv on 26/08/23.
//

#ifndef DISCOVERING_STM32_TIMER_H
#define DISCOVERING_STM32_TIMER_H
#include <stm32f10x.h>

void Delay(uint32_t nTime);

void configure_timer(uint32_t divider);

#endif //DISCOVERING_STM32_TIMER_H
