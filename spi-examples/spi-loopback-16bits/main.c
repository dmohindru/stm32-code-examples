#include "rcc-config.h"
#include "spi-config.h"
uint8_t txbuf[4], rxbuf[4];
uint16_t txbuf16[4], rxbuf16[4];

void chip_select_pin_init();
void assert_failed(uint8_t* file , uint32_t line);
void Delay( uint32_t nTime );

int main() {
    int i, j;

    clock_init();
    // TODO: To implement
    chip_select_pin_init();
    spiInit(SPI2);

    // Test 8 bit transfer
    while(1) {

        // Test 16 bit transfer
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 4; j++) {
                txbuf16[j] = i*4 + j + (i<<8);
            }

            GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
            spiReadWrite16(SPI2, rxbuf16, txbuf16, 4, SPI_SLOW);
            GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

            for (j = 0; j < 4; j++) {
                if (rxbuf16[j] != txbuf16[j]) {
                    //assert_failed(__FILE__, __LINE__);
                }
            }
        }

    }




    return 0;

}

void chip_select_pin_init() {
    GPIO_InitTypeDef  gpio_init_typedef;

    // Enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Configure pin
    GPIO_StructInit(&gpio_init_typedef);
    gpio_init_typedef.GPIO_Pin = GPIO_Pin_12;
    gpio_init_typedef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_typedef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init_typedef);

    // Write on chip select pin
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

}

static __IO uint32_t TimingDelay;
void Delay( uint32_t nTime ){
    TimingDelay = nTime;
    while (TimingDelay != 0);
}
void SysTick_Handler (void){
    if (TimingDelay != 0x00)
        TimingDelay--;
}

//#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file , uint32_t line)
{
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
//#endif
