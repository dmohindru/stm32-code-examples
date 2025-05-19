# STM32F3Discovery Board Project Ideas (TDD in Rust)

These projects use **only the onboard hardware** of the STM32F3Discovery board and are ideal for learning **Test-Driven Development (TDD)** in embedded Rust.

---

## 1. Orientation Tracker

**Goal:**  
Track the board’s orientation using the gyroscope and accelerometer.

**Peripherals:**

- L3GD20 (Gyroscope) - SPI
- LSM303DLHC (Accelerometer) - I²C
- LEDs

**TDD Targets:**

- Sensor drivers (SPI & I²C)
- Sensor fusion logic
- Calibration routines

**UI:**  
Use LEDs to indicate direction of tilt (e.g., LED1 = tilt left, LED2 = tilt right).

---

## 2. Reaction Timer Game

**Goal:**  
Light up a random LED after a random delay. Press the user button as fast as possible.

**Peripherals:**

- User Button
- LEDs
- SysTick (for delays)

**TDD Targets:**

- Debouncing logic
- State machine transitions
- Random delay logic

**UI:**  
LEDs display how fast the reaction was (e.g., LED1 = fast, LED4 = slow).

---

## 3. Gesture-Based LED Control

**Goal:**  
Detect gestures like shakes or tilts to trigger LED patterns.

**Peripherals:**

- Accelerometer
- LEDs

**TDD Targets:**

- Motion event detection
- Gesture recognition logic
- LED pattern mapping

**UI:**  
Shake = toggle all LEDs. Tilt left = left-side LEDs on, right = right-side on.

---

## 4. Electronic Compass

**Goal:**  
Use the magnetometer to build a digital compass.

**Peripherals:**

- Magnetometer (part of LSM303DLHC)
- LEDs

**TDD Targets:**

- Magnetometer driver
- Heading calculation logic
- Direction-to-LED mapping

**UI:**  
Map cardinal directions to specific LEDs.

---

## 5. Movement Logger

**Goal:**  
Continuously log accelerometer/gyro data and stream to a host computer.

**Peripherals:**

- Accelerometer & Gyroscope
- USB (via semihosting or RTT)

**TDD Targets:**

- Data acquisition logic
- Logging/buffering mechanism
- USB/RTT communication protocol

**UI:**  
No UI on the board—data sent to host.

---

## 6. Level Checker (User Idea)

**Goal:**  
Turn on all LEDs when level. Turn off LEDs on the tilted side as the board tilts.

**Peripherals:**

- Accelerometer
- LEDs

**TDD Targets:**

- Angle calculation from acceleration
- LED mapping based on tilt direction
- Optional: calibration logic

**UI:**

- Perfectly flat: all LEDs ON
- Tilt left: left LEDs OFF
- Tilt right: right LEDs OFF
- Tilt forward/back: top/bottom LEDs OFF

---

**Tools to Use:**

- `embedded-hal`
- `embedded-hal-mock` for unit tests
- `defmt`, `probe-rs`, or `cargo-embed` for on-target testing
- RTIC for real-time task organization (optional)

---

## 7. Full-Stack IoT Control & Monitoring System with STM32F3Discovery

This project implements a full-stack IoT system using only the STM32F3Discovery board and standard tools. It features a command-based interface over USART, a Rust backend server, and a React-based web UI. All components are developed using **Test-Driven Development (TDD)**.

**Goal:**

- Control onboard peripherals (LEDs) via UART commands
- Register/deregister sensor data logging tasks
- Stream and manage sensor data (Gyroscope, Compass)
- View and control everything through a React-based UI
- Develop all components (Firmware, Server, Web UI) using TDD practices

### System Architecture

- **STM32F3**: Parses commands, controls LEDs, and manages sensor logging
- **Rust Server**: Talks to board via serial port and exposes HTTP/WebSocket APIs
- **React UI**: Sends commands and visualizes board state and sensor data

### STM32F3 Firmware

**Responsibilities:**

- Parse UART commands (text-based or binary)
- Control 8 onboard LEDs
- Interface with LSM303DLHC (Compass) and L3GD20 (Gyro)
- Register and run periodic logging tasks (using timer interrupt)
- Send structured sensor logs back over UART

**Commands:**

- `led on <n>` – Turn on LED `n`
- `led off <n>` – Turn off LED `n`
- `log compass <interval>` – Start logging compass at `interval` ms
- `log gyro <interval>` – Start logging gyro at `interval` ms
- `stop <sensor>` – Stop logging for sensor
- `status` – Get all registered logging tasks

**TDD Targets:**

- UART parser unit tests
- Sensor driver mocks
- Timer and task scheduler tests
- Integration tests over serial interface

### Rust Server

**Responsibilities:**

- Connect to STM32F3 via serial (USB)
- Send commands, receive logs
- Provide HTTP/WebSocket API for UI
- Maintain task state and data buffers

**Features:**

- `POST /led` – Control LED
- `POST /log` – Register sensor logging
- `DELETE /log` – Deregister logging task
- `GET /status` – Get board state
- `GET /logs` – Get recent sensor data

**TDD Targets:**

- Unit tests for command encoding/decoding
- Integration tests with mock serial
- REST API unit and integration tests
- Async task polling with timer mocks

### React Web UI

**Responsibilities:**

- User controls for LEDs and sensors
- Display registered tasks and system status
- Real-time display of compass/gyro data
- Full CRUD interface to control the board

**Stack:**

- React + TypeScript
- Jest + React Testing Library for TDD
- Cypress for E2E testing

**TDD Targets:**

- Unit tests for hooks and state logic
- Component-level testing of all UI elements
- E2E tests simulating full system interaction

### Development & TDD Tools

- **STM32F3**: `probe-rs`, `defmt`, `embedded-hal-mock`, `cargo-embed`
- **Rust Server**: `tokio`, `serialport`, `axum` or `actix-web`, `serde`, `rstest`
- **React UI**: `vite`, `jest`, `@testing-library/react`, `cypress`

### Future Extensions

- Add persistent storage (e.g., log to SD card or server DB)
- Add support for custom logging formats (JSON, CBOR)
- Use MQTT or gRPC instead of HTTP/WebSocket
- Host React UI on Raspberry Pi 4 to manage remote F3 boards

### Learning Outcomes

- TDD across embedded, backend, and frontend
- Serial communication protocol design
- Full-stack system design and implementation
- Embedded sensor driver development
- Async programming in Rust and JavaScript

### License

MIT

---
