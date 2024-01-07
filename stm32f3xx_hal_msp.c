#include "stm32f3xx_hal.h"

#include "conf_winc.h"


void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI_INSTANCE) {
        GPIO_InitTypeDef gpio_init = {0};

        SPI_CLK_ENABLE();
        SPI_NSS_CLK_ENABLE();
        SPI_SCK_CLK_ENABLE();
        SPI_MISO_CLK_ENABLE();
        SPI_MOSI_CLK_ENABLE();

        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Pull = GPIO_NOPULL;
        gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init.Alternate = SPI_GPIO_AF;

        gpio_init.Pin = SPI_NSS_PIN;
        HAL_GPIO_Init(SPI_NSS_PORT, &gpio_init);

        gpio_init.Pin = SPI_SCK_PIN;
        HAL_GPIO_Init(SPI_SCK_PORT, &gpio_init);

        gpio_init.Pin = SPI_MISO_PIN;
        HAL_GPIO_Init(SPI_MISO_PORT, &gpio_init);

        gpio_init.Pin = SPI_MOSI_PIN;
        HAL_GPIO_Init(SPI_MOSI_PORT, &gpio_init);
    }
}


void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI_INSTANCE) {
        SPI_CLK_DISABLE();
        HAL_GPIO_DeInit(SPI_NSS_PORT, SPI_NSS_PIN);
        HAL_GPIO_DeInit(SPI_SCK_PORT, SPI_SCK_PIN);
        HAL_GPIO_DeInit(SPI_MISO_PORT, SPI_MISO_PIN);
        HAL_GPIO_DeInit(SPI_MOSI_PORT, SPI_MOSI_PIN);
    }
}