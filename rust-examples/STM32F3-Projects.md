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
