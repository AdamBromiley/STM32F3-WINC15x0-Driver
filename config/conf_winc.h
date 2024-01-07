#ifndef CONF_WINC_H
#define CONF_WINC_H


#include <stdint.h>
#include <stdio.h>

#include "stm32f3xx_hal.h"


#define CONF_WINC_USE_SPI (1)
#define CONF_WINC_DEBUG 1
#define CONF_WINC_PRINTF printf


/* Clock-enable/disable macros (defined here and must match with ports and
 * enabled peripherals in conf_winc.c).
 */
#define WINC_RESET_N_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define WINC_CHIP_EN_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define WINC_IRQN_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_CLK_ENABLE() __HAL_RCC_SPI1_CLK_ENABLE()
#define SPI_CLK_DISABLE() __HAL_RCC_SPI1_CLK_DISABLE()
#define SPI_NSS_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_SCK_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_MISO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_MOSI_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()


/* Configuration for non-SPI pins connected to the WINC15x0. */
extern GPIO_TypeDef *WINC_RESET_N_PORT;
extern const uint16_t WINC_RESET_N_PIN;

extern GPIO_TypeDef *WINC_CHIP_EN_PORT;
extern const uint16_t WINC_CHIP_EN_PIN;

extern GPIO_TypeDef *WINC_IRQN_PORT;
extern const uint16_t WINC_IRQN_PIN;
extern const IRQn_Type WINC_IRQN_TYPE;


/* SPI pin configuration. */
extern SPI_TypeDef *SPI_INSTANCE;

extern GPIO_TypeDef *SPI_NSS_PORT;
extern const uint16_t SPI_NSS_PIN;

extern GPIO_TypeDef *SPI_SCK_PORT;
extern const uint16_t SPI_SCK_PIN;

extern GPIO_TypeDef *SPI_MISO_PORT;
extern const uint16_t SPI_MISO_PIN;

extern GPIO_TypeDef *SPI_MOSI_PORT;
extern const uint16_t SPI_MOSI_PIN;

extern const uint32_t SPI_GPIO_AF;


#endif
