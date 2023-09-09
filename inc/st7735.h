
#ifndef ST7335_H
#define ST7335_H

/*  Colors are 565 RGB (5 bits Red, 6 bits green, 5 bits blue) */

#define BLACK           0x0000
#define RED             0x001F
#define GREEN           0x07E0
#define CYAN            0xFFE0
#define BLUE            0xF800
#define MAGENTA         0xF81F
#define YELLOW          0x07FF
#define WHITE           0xFFFF

#define SPILCD SPI2

/* MADCTL [MY MX MV]
 *    MY  row address order   1 (bottom to top), 0 (top to bottom)
 *    MX  col address order   1 (right to left), 0 (left to right)
 *    MV  col/row exchange    1 (exchange),      0 normal
 */

#define MADCTLGRAPHICS 0x6
#define MADCTLTEXT 0x7
#define MADCTLBMP      0x2

typedef struct ST7735_Def {
    SPI_TypeDef *spi_x;
    GPIO_TypeDef *gpio_port;
    uint16_t backlit;
    uint16_t reset;
    uint16_t chip_select;
    uint16_t dc;
    uint16_t width;
    uint16_t height;

} ST7735_Def;

void st7735_lcd_init(struct ST7735_Def *lcd_init_struct);

void st7735_lcd_set_addr_window(struct ST7735_Def *lcd_init_struct,
        uint16_t x0,
        uint16_t y0,
        uint16_t x1,
        uint16_t y1,
        uint8_t madctl);

void st7735_lcd_push_color(struct ST7735_Def *lcd_init_struct, uint16_t *color, int cnt);

void st7735_lcd_back_light(struct ST7735_Def *lcd_init_struct, uint8_t on);

void st7735_lcd_fill_screen(struct ST7735_Def *lcd_init_struct, uint16_t color);

void st7735_draw_char(struct ST7735_Def *lcd_init_struct,
        char letter,
        uint16_t letter_color,
        uint16_t bg_color,
        uint16_t start_x,
        uint16_t start_y);

void st7735_draw_str(struct ST7735_Def *lcd_init_struct,
                      char *str,
                      uint16_t letter_color,
                      uint16_t bg_color,
                      uint16_t start_x,
                      uint16_t start_y);

#endif
