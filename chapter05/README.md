### List of exercises
1. [UART hello](ex-5-1-uart-hello): This program demonstrates how to use UART and periodically transmits 'Hello World'
2. [UART hello parallel](ex-5-2-uart-hello-parallel): Program to use multiple UART and periodically transmits message. For eg
   - UART1: transmits 'Hello from UART1' @ baud rate = 9600
   - UART2: transmits 'Hello from UART2' @ baud rate = 19200
3. [UART echo](ex-5-3-uart-echo): Program to echo back messages received from host PC.
4. [UART echo second](ex-5-4-uart-echo-second): This program listens for messages on UART1 and transmits UART2.
5. [UART processor](ex-5-5-uart-processor): This program does message processing received via UART
   - Received message string on UART1 from host machine
   - Does simple processing like converting received text to upper case
   - Transmit message back to host machine
   - Does string message processing using [picolibc library](https://github.com/picolibc/picolibc)
6. [UART text command](ex-5-6-uart-text-command): This program received a text command over uart and accordingly turn on and off on board led.
7. [UART lib](uart-lib): This contains command code required to initialise GPIO and UART subsystem of STM32 blue-pill.

### Notes
It has been observed that whatever baud rate is set on STM32 half of it is understood by USB TTL device.
For example: 
If baud rate at STM32 is set at 9600 then set baud rate to listen on /ttyUSB0 at 4800.