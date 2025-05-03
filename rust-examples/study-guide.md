# 📘 Embedded Rust Learning Roadmap

### Discovery Book + Embedded Rust Book Integration

## 🎯 Goal

Use the [**Discovery Book**](https://docs.rust-embedded.org/discovery/) to build real projects on STM32F3 and deepen your understanding with the [**Embedded Rust Book**](https://docs.rust-embedded.org/book/) as a companion reference.

---

## 🗺️ Roadmap Overview

| Discovery Book Chapter                                                                                                | Embedded Rust Book Section                                                        | Purpose                                                  |
| --------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------- | -------------------------------------------------------- |
| [**Chapter 1: Introduction**](https://docs.rust-embedded.org/discovery/f3discovery/01-setup/index.html)               | [Intro, Tooling](https://docs.rust-embedded.org/book/intro/index.html)            | Understand the embedded Rust ecosystem and prerequisites |
| [**Chapter 2: Blinky (Hello World)**](https://docs.rust-embedded.org/discovery/f3discovery/02-blinky/index.html)      | [Install Toolchain](https://docs.rust-embedded.org/book/intro/install.html)       | Flash your first program to the board                    |
| [**Chapter 3: Memory-Mapped Registers**](https://docs.rust-embedded.org/discovery/f3discovery/03-mitm/index.html)     | [no_std, Registers](https://docs.rust-embedded.org/book/start/registers.html)     | Low-level bare-metal control using `no_std`              |
| [**Chapter 4: GPIO HAL (High-Level)**](https://docs.rust-embedded.org/discovery/f3discovery/04-pins/index.html)       | [HALs and PACs](https://docs.rust-embedded.org/book/peripherals/index.html)       | Learn safe abstractions using HAL crates                 |
| [**Chapter 5: Digital Input**](https://docs.rust-embedded.org/discovery/f3discovery/05-led-roulette/index.html)       | [GPIO Input](https://docs.rust-embedded.org/book/peripherals/gpio.html)           | Reading state from GPIO pins                             |
| [**Chapter 6: The Accelerometer**](https://docs.rust-embedded.org/discovery/f3discovery/06-accelerometer/index.html)  | [I2C & Drivers](https://docs.rust-embedded.org/book/peripherals/i2c.html)         | Use embedded-hal traits to communicate with devices      |
| [**Chapter 7: The Magnetometer**](https://docs.rust-embedded.org/discovery/f3discovery/07-magnetometer/index.html)    | Same as above                                                                     | Practice I2C again with another sensor                   |
| [**Chapter 8: The Display**](https://docs.rust-embedded.org/discovery/f3discovery/08-led-compass/index.html)          | [SPI + Display Drivers](https://docs.rust-embedded.org/book/peripherals/spi.html) | Output compass direction via LEDs                        |
| [**Chapter 9: Concurrency with RTIC**](https://docs.rust-embedded.org/discovery/f3discovery/09-rtic/index.html)       | [RTIC](https://docs.rust-embedded.org/book/concurrency/rtic.html)                 | Learn real-time multitasking safely                      |
| [**Chapter 10: Serial Communication**](https://docs.rust-embedded.org/discovery/f3discovery/10-serial/index.html)     | [Serial/UART](https://docs.rust-embedded.org/book/peripherals/serial.html)        | Logging and debugging through UART                       |
| [**Chapter 11: Logging and Debugging**](https://docs.rust-embedded.org/discovery/f3discovery/11-debugging/index.html) | [Debugging](https://docs.rust-embedded.org/book/start/debugging.html)             | Use GDB, logging macros, and semihosting                 |
| [**Chapter 12: Final Project**](https://docs.rust-embedded.org/discovery/f3discovery/12-final-project/index.html)     | Review previous sections                                                          | Combine everything into a complete application           |

---

## 🔁 Suggested Study Cycle

1. **Work through a Discovery Book chapter**
2. **Pause to consult Embedded Rust Book for deeper concepts**
3. **Experiment**: Modify, extend, and reflect
4. **Repeat with the next chapter**

---

## 🛠 Hardware Needed

- STM32F3 Discovery Board (`stm32f3discovery`)
- Micro-USB cable
- Linux/macOS/WSL2 for best compatibility
- Optional: External sensors, breadboard, jump wires

---

## ✅ Final Project Ideas

- Digital compass using accelerometer + magnetometer
- Reaction timer game using button interrupts
- Data logger with UART + sensor input
- Real-time LED pattern based on orientation

---

## 💡 Tips

- Use `cargo embed`, `probe-rs`, `gdb`, and `defmt` for workflows
- Join the [Rust Embedded Matrix chat](https://matrix.to/#/#rust-embedded:matrix.org)
- Reference [embedded-hal](https://docs.rs/embedded-hal/) traits when working with I2C/SPI/UART devices
- Stay updated at [https://rust-embedded.org](https://rust-embedded.org)

---

## Links

- [Quick starter link for any board](https://docs.rust-embedded.org/cortex-m-quickstart/cortex_m_quickstart/)

Happy hacking with Embedded Rust 🚀🦀
