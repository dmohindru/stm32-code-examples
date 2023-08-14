#include "rcc-config.h"
#include "spi-config.h"
uint8_t txbuf[4], rxbuf[4];
uint16_t txbuf16[4], rxbuf16[4];

void csInit() {

}
int main() {
    int i, j;

    // TODO: To implement
    csInit();
    spiInit(SPI2);

    // Test 8 bit transfer
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {

        }
    }


    // Test 16 bit transfer
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {

        }
    }

}
