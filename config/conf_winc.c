#include "conf_winc.h"

#include <stdint.h>

#include "stm32f3xx_hal.h"


/* Configuration for non-SPI pins connected to the WINC15x0. */
const uint16_t WINC_RESET_N_PIN = GPIO_PIN_0;
GPIO_TypeDef *WINC_RESET_N_PORT = GPIOA;

const uint16_t WINC_CHIP_EN_PIN = GPIO_PIN_1;
GPIO_TypeDef *WINC_CHIP_EN_PORT = GPIOA;

const uint16_t WINC_IRQN_PIN = GPIO_PIN_3;
GPIO_TypeDef *WINC_IRQN_PORT = GPIOA;
const IRQn_Type WINC_IRQN_TYPE = EXTI3_IRQn;


/* SPI pin configuration. */
SPI_TypeDef *SPI_INSTANCE = SPI1;

GPIO_TypeDef *SPI_NSS_PORT = GPIOA;
const uint16_t SPI_NSS_PIN = GPIO_PIN_4;

GPIO_TypeDef *SPI_SCK_PORT = GPIOA;
const uint16_t SPI_SCK_PIN = GPIO_PIN_5;

GPIO_TypeDef *SPI_MISO_PORT = GPIOA;
const uint16_t SPI_MISO_PIN = GPIO_PIN_6;

GPIO_TypeDef *SPI_MOSI_PORT = GPIOA;
const uint16_t SPI_MOSI_PIN = GPIO_PIN_7;

const uint32_t SPI_GPIO_AF = GPIO_AF5_SPI1;
