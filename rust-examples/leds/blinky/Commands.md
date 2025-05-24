openocd -s "$HOME/opt/pico/openocd/tcl" -f interface/stlink.cfg -f target/stm32f3x.cfg -c "program leds verify reset exit"
