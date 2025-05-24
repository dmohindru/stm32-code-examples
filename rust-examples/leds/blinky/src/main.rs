#![no_std]
#![no_main]

// pick a panicking behavior
use panic_halt as _; // you can put a breakpoint on `rust_begin_unwind` to catch panics
                     // use panic_abort as _; // requires nightly
                     // use panic_itm as _; // logs messages over ITM; requires ITM support
                     // use panic_semihosting as _; // logs messages to the host stderr; requires a debugger

// use cortex_m::asm;
use cortex_m_rt::entry;

use stm32f3_discovery::{leds::Leds, stm32f3xx_hal, switch_hal};
use switch_hal::OutputSwitch;

use stm32f3xx_hal::prelude::*;
use stm32f3xx_hal::{delay::Delay, hal::blocking::delay::DelayMs, pac};

#[entry]

fn main() -> ! {
    let (mut leds, mut delay) = setup();
    loop {
        leds.ld3.on().ok();
        leds.ld5.on().ok();
        leds.ld7.on().ok();
        delay.delay_ms(1000_u16);

        leds.ld3.off().ok();
        leds.ld5.off().ok();
        leds.ld7.off().ok();
        delay.delay_ms(1000_u16);
    }
}

fn setup() -> (Leds, Delay) {
    let dp = pac::Peripherals::take().unwrap();
    let mut rcc = dp.RCC.constrain();

    let cp = cortex_m::Peripherals::take().unwrap();
    let mut flash = dp.FLASH.constrain();
    let clocks = rcc.cfgr.freeze(&mut flash.acr);
    let delay = Delay::new(cp.SYST, clocks);
    let mut gpioe = dp.GPIOE.split(&mut rcc.ahb);

    let leds = Leds::new(
        gpioe.pe8,
        gpioe.pe9,
        gpioe.pe10,
        gpioe.pe11,
        gpioe.pe12,
        gpioe.pe13,
        gpioe.pe14,
        gpioe.pe15,
        &mut gpioe.moder,
        &mut gpioe.otyper,
    );

    (leds, delay)
}
