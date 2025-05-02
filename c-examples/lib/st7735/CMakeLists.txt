add_library(st7735 STATIC st7735.c)
target_link_libraries(st7735 PRIVATE stm32_common_starter)