/***************************************************
  This is a library for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

/*
 The code contained here is based upon the adafruit driver, but heavily modified
*/

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "spi-config.h"
#include "st7735.h"
#include "timer.h"
#include "glcdfont.h"

#define LCDSPEED SPI_FAST

#define LOW  0
#define HIGH 1

#define LCD_C LOW
#define LCD_D HIGH

#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_MADCTL 0x36
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E
#define ST7735_COLMOD 0x3A

#define MADVAL(x) (((x) << 5) | 8)
static uint8_t madctlcurrent = MADVAL(MADCTLGRAPHICS);

struct ST7735_cmdBuf {
    uint8_t command;   // ST7735 command byte
    uint8_t delay;     // ms delay after
    uint8_t len;       // length of parameter data
    uint8_t data[16];  // parameter data
};

static const struct ST7735_cmdBuf initializers[] = {
        // SWRESET Software reset
        {0x01,          150, 0,  0},
        // SLPOUT Leave sleep mode
        {0x11,          150, 0,  0},
        // FRMCTR1, FRMCTR2 Frame Rate configuration -- Normal mode, idle
        // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
        {0xB1,          0,   3,  {0x01, 0x2C, 0x2D}},
        {0xB2,          0,   3,  {0x01, 0x2C, 0x2D}},
        // FRMCTR3 Frame Rate configureation -- partial mode
        {0xB3,          0,   6,  {0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D}},
        // INVCTR Display inversion (no inversion)
        {0xB4,          0,   1,  {0x07}},
        // PWCTR1 Power control -4.6V, Auto mode
        {0xC0,          0,   3,  {0xA2, 0x02, 0x84}},
        // PWCTR2 Power control VGH25 2.4C, VGSEL -10, VGH = 3 * AVDD
        {0xC1,          0,   1,  {0xC5}},
        // PWCTR3 Power control, opamp current smal, boost frequency
        {0xC2,          0,   2,  {0x0A, 0x00}},
        // PWCTR4 Power control, BLK/2, opamp current small and medium low
        {0xC3,          0,   2,  {0x8A, 0x2A}},
        // PWRCTR5, VMCTR1 Power control
        {0xC4,          0,   2,  {0x8A, 0xEE}},
        {0xC5,          0,   1,  {0x0E}},
        // INVOFF Don't invert display
        {0x20,          0,   0,  0},
        // Memory access directions. row address/col address, bottom to top refesh (10.1.27)
        {ST7735_MADCTL, 0,   1,  {MADVAL(MADCTLGRAPHICS)}},
        // Color mode 16 bit (10.1.30
        {ST7735_COLMOD, 0,   1,  {0x05}},
        // Column address set 0..127
        {ST7735_CASET,  0,   4,  {0x00, 0x00, 0x00, 0x7F}},
        // Row address set 0..159
        {ST7735_RASET,  0,   4,  {0x00, 0x00, 0x00, 0x9F}},
        // GMCTRP1 Gamma correction
        {0xE0,          0,   16, {0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D,
                                         0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10}},
        // GMCTRP2 Gamma Polarity corrction
        {0xE1,          0,   16, {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
                                         0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10}},
        // DISPON Display on
        {0x29,          100, 0,  0},
        // NORON Normal on
        {0x13,          10,  0,  0},
        // End
        {0,             0,   0,  0}
};

static void lcd_write(struct ST7735_Def *lcd_struct, char dc, const char *data, int nbytes) {
    GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->dc, dc);  // dc 1 = data, 0 = control
    GPIO_ResetBits(lcd_struct->gpio_port, lcd_struct->chip_select);
    spiReadWrite(lcd_struct->spi_x, 0, data, nbytes, LCDSPEED);
    GPIO_SetBits(lcd_struct->gpio_port, lcd_struct->chip_select);
}

static void lcd_write16(struct ST7735_Def *lcd_struct, char dc, const uint16_t *data, int cnt) {
    GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->dc, dc);  // dc 1 = data, 0 = control
    GPIO_ResetBits(lcd_struct->gpio_port, lcd_struct->chip_select);
    spiReadWrite16(lcd_struct->spi_x, 0, data, cnt, LCDSPEED);
    GPIO_SetBits(lcd_struct->gpio_port, lcd_struct->chip_select);
}

static void lcd_write_cmd(struct ST7735_Def *lcd_struct, uint8_t c) {
    lcd_write(lcd_struct, LCD_C, &c, 1);
}

void st7735_lcd_init(struct ST7735_Def *lcd_struct) {
    GPIO_InitTypeDef GPIO_InitStructure;
    const struct ST7735_cmdBuf *cmd;

    // set up pins and clocks
    uint32_t gpio_peripheral;
    if (lcd_struct->gpio_port == GPIOA) {
        gpio_peripheral = RCC_APB2Periph_GPIOA;
    } else if (lcd_struct->gpio_port == GPIOB) {
        gpio_peripheral = RCC_APB2Periph_GPIOB;
    } else {
        gpio_peripheral = RCC_APB2Periph_GPIOC;
    }
    RCC_APB2PeriphClockCmd(gpio_peripheral, ENABLE);

    // Setup GPIO
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = lcd_struct->reset | lcd_struct->chip_select | lcd_struct->dc;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(lcd_struct->gpio_port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = lcd_struct->backlit;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(lcd_struct->gpio_port, &GPIO_InitStructure);

    // Initialize SPI
    spiInit(lcd_struct->spi_x);

    // set cs, reset low
    GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->chip_select, HIGH);
    GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->reset, HIGH);
    Delay(10);
    GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->reset, LOW);
    Delay(10);
    GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->reset, HIGH);
    Delay(10);

    // Send initialization commands to ST7735

    for (cmd = initializers; cmd->command; cmd++) {
        lcd_write(lcd_struct, LCD_C, &(cmd->command), 1);
        if (cmd->len)
            lcd_write(lcd_struct, LCD_D, cmd->data, cmd->len);
        if (cmd->delay)
            Delay(cmd->delay);
    }

    // Set backlight on
    st7735_lcd_back_light(lcd_struct, HIGH);

}

void st7735_lcd_set_addr_window(struct ST7735_Def *lcd_struct, uint16_t x0,
        uint16_t y0, uint16_t x1,
        uint16_t y1, uint8_t madctl) {
    madctl = MADVAL(madctl);
    if (madctl != madctlcurrent) {
        lcd_write_cmd(lcd_struct, ST7735_MADCTL);
        lcd_write(lcd_struct, LCD_D, &madctl, 1);
        madctlcurrent = madctl;
    }
    lcd_write_cmd(lcd_struct, ST7735_CASET);
    lcd_write16(lcd_struct, LCD_D, &x0, 1);
    lcd_write16(lcd_struct, LCD_D, &x1, 1);

    lcd_write_cmd(lcd_struct, ST7735_RASET);
    lcd_write16(lcd_struct, LCD_D, &y0, 1);
    lcd_write16(lcd_struct, LCD_D, &y1, 1);

    lcd_write_cmd(lcd_struct, ST7735_RAMWR);
}

void st7735_lcd_back_light(struct ST7735_Def *lcd_struct, uint8_t on) {
    if (on)
        GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->backlit, HIGH);
    else
        GPIO_WriteBit(lcd_struct->gpio_port, lcd_struct->backlit, LOW);
}

void st7735_lcd_push_color(struct ST7735_Def *lcd_struct, uint16_t *color, int cnt) {
    lcd_write16(lcd_struct, LCD_D, color, cnt);
}

void st7735_lcd_fill_screen(struct ST7735_Def *lcd_struct, uint16_t color) {
    uint8_t x, y;

    st7735_lcd_set_addr_window(lcd_struct,
                               0,
                               0,
                               lcd_struct->width - 1,
                               lcd_struct->height - 1,
                               MADCTLGRAPHICS);

    for (x = 0; x < lcd_struct->width; x++)
    {
        for (y = 0; y < lcd_struct->height; y++)
        {
            st7735_lcd_push_color(lcd_struct, &color, 1);
        }
    }
}

void st7735_draw_char(struct ST7735_Def *lcd_init_struct, char letter,
        uint16_t letter_color, uint16_t bg_color,
        uint16_t start_x, uint16_t start_y) {

    //Step 1: determine where we are in the font array
    uint16_t location_in_font_array = 5*letter; //converts to a number and 5x to get pos. in font array

    //Step 2: set our window - start x,y + room as described in the book
    //each character is placed in a 10x7 (x is top down, y is left right) rectangle leaving
    //space between lines (3 pixels) and characters (1 pixel)
    st7735_lcd_set_addr_window(lcd_init_struct,
                               start_x,
                               start_y,
                               start_x+9,
                               start_y+6,
                               MADCTLGRAPHICS);

    //Step 3:
    //for all 5 bytes that compose the letter
    for(uint8_t i=0; i<5; i++) //each loop is another defining of a "column" by the 8bit hex value
    {
        //get the hex value in font
        uint8_t font_hex = ASCII[location_in_font_array +i];

        //for each bit in the hex value byte
        for(uint8_t j=0; j<8; j++)
        {
            if(font_hex & 1) //if the last bit is a 1
            {
                st7735_lcd_push_color(lcd_init_struct, &letter_color,1); //its part of the letter
            }
            else
            {
                st7735_lcd_push_color(lcd_init_struct, &bg_color,1); //otherwise, its background.
            }

            font_hex = font_hex >> 1; //right shift out the used bit
        }

        // draw line spacing
        for(uint8_t k=0;k<2;k++) //row 9 and 10 are blank
        {
            st7735_lcd_push_color(lcd_init_struct, &bg_color,1);
        }


    }
    //write same 2 bytes  10 times for the spacing.
    //Based on M. minkowski's implentation,
    //I dont trust setting cnt in pushColor to 10
    //Change loop count to get sanity check for how it writes top-down
    for(int k = 0; k<10;k++)
    {
        st7735_lcd_push_color(lcd_init_struct, &bg_color,1); //write background to the 5th column
    }

}
