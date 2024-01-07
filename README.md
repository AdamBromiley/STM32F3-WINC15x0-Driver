# STM32F3 WINC15x0 Driver
Microchip's WINC driver for the ATWINC15x0, ported for the STM32F3 series of microcontrollers.

This is currently the latest version of the driver, 19.7.7, which is shipped with the Atmel Advanced Software Framework (ASF).

## General Usage
**Prerequisites:** this driver depends on the STM32Cube HAL API for the STM32F3 series.

> **Warning:** when using STM32CubeIDE, do not use the project's `.ioc` configuration file to enable/configure the GPIO or SPI pins that connect to the WINC15x0 board. This driver package will configure them as needed.

*See bullet points for instructions specific to already-initialised STM32CubeIDE projects.*

1. Copy the `WINC15x0` folder into your project.
    - Copy into the `Drivers/` folder.
2. Copy the contents of `stm32f3xx_it.c` into whatever source file you use for interrupt handler definitions.
    - Just copy the contents into the existing `Src/stm32f3xx_it.c` file.
3. Repeat with the contents of `stm32f3xx_hal_msp.c`.
4. Add the driver folder to your include path list.
    - Go to *Project > Properties > C/C++ Build > Settings > Tool Settings > MCU GCC Compiler > Include paths*, and place `../Drivers/WINC15x0` in the *Include paths (-I)* list.
5. Similarly, add the configuration folder as an include path.
    - This would be `../Drivers/WINC15x0/config` in STM32CubeIDE.
6. To properly include the board support package, define the `STM32F3` macro when compiling.
    - Go to *... > MCU GCC Compiler > Preprocessor*, and add `STM32F3` to the *Define symbols (-D)* list.
7. Change the pin configuration, if necessary, in `config/conf_winc.c` and `config/conf_winc.h`. See [Pin configuration](#pin-configuration).

## Pin configuration
The ATWINC15x0's RESET_N, CHIP_EN, and IRQN pins can be connected to any unused GPIO pin on the STM32. The SPI pins must be connected to STM32 GPIO pins that have an alternative function mapping to the chosen SPI instance.

This driver was originally tested and used with an STM32F303K8, which has only one SPI instance (SPI1). Therefore, the alternate function number and GPIO ports and pin numbers all align to those for SPI1, as documented in the STM32F303x6/x8 datasheet. If using this driver with a different STM32F3 microcontroller, the values in `config/conf_winc.c` and clock enable/disable macros in `config/conf_winc.h` may require changing.

The default pin configuration of the driver is shown below. Physical pin mappings of the Xplained Pro and Nucleo development boards have been included as an example to assist in understanding.

| ATWINC15x0 pin | STM32 pin | ATWINC15x0-XPRO pin | NUCLEO-F303K8 pin | Wire colour |
|----------------|-----------|---------------------|-------------------|-------------|
| RESET_N        | PA0       | 5                   | A0                | Grey        |
| CHIP_EN        | PA1       | 10                  | A1                | Brown       |
| IRQN           | PA3       | 9                   | A2                | Orange      |
| SPI_SSN        | PA4       | 15                  | A3                | Green       |
| SPI_SCK        | PA5       | 18                  | A4                | White       |
| SPI_MISO       | PA6       | 17                  | A5                | Blue        |
| SPI_MOSI       | PA7       | 16                  | A6                | Purple      |
| GND            | N/A       | 19                  | GND               | Black       |
| VCC_TARGET     | N/A       | 20                  | +3V3              | Yellow      |
