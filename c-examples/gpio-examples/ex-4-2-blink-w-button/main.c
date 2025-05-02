#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

// onboard led pin: PC13
// push button pin: PB0
// output blue led pin: PC14
void Delay(uint32_t nTime);

int main(void) {

    // Enable Peripheral Clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

    // Instantiate and initialize gpio config structure
    GPIO_InitTypeDef gpio_InitTypeDef;
    GPIO_StructInit(&gpio_InitTypeDef);

    // Configure output LEDs PC13, PC14
    gpio_InitTypeDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    gpio_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_InitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpio_InitTypeDef);

    // Configure input in PB0
    gpio_InitTypeDef.GPIO_Pin = GPIO_Pin_0;
    gpio_InitTypeDef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &gpio_InitTypeDef);


    // Configure SysTick Timer
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }

    while (1) {

        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_SET) {
            GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_SET);
        } else {
            GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_RESET);
        }


        static int ledval = 0;
        // toggle led
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (ledval) ? Bit_SET : Bit_RESET);

        ledval = 1 - ledval;

        Delay(250);
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


#ifdef USE_FULL_ASSERT
void assert_failed ( uint8_t * file , uint32_t line)
{
/* Infinite loop */
/* Use GDB to find out why we're here */
while (1);
}
#endif