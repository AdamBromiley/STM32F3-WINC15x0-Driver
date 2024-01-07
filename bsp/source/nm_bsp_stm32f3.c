#include "bsp/include/nm_bsp_stm32f3.h"

#include "stm32f3xx_hal.h"

#include "bsp/include/nm_bsp.h"
#include "common/include/nm_common.h"
#include "conf_winc.h"


tpfNmBspIsr gpfIsr = NULL;


static void init_chip_pins(void);


static void init_chip_pins(void) {
    GPIO_InitTypeDef gpio_init = {0};

    WINC_RESET_N_CLK_ENABLE();
    WINC_CHIP_EN_CLK_ENABLE();

    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_PULLDOWN;
    gpio_init.Speed = GPIO_SPEED_FREQ_LOW;

    gpio_init.Pin = WINC_RESET_N_PIN;
    HAL_GPIO_Init(WINC_RESET_N_PORT, &gpio_init);

    gpio_init.Pin = WINC_CHIP_EN_PIN;
    HAL_GPIO_Init(WINC_CHIP_EN_PORT, &gpio_init);

    HAL_GPIO_WritePin(WINC_RESET_N_PORT, WINC_RESET_N_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(WINC_CHIP_EN_PORT, WINC_CHIP_EN_PIN, GPIO_PIN_RESET);
}


sint8 nm_bsp_init(void) {
    gpfIsr = NULL;

    init_chip_pins();
    HAL_InitTick(0);
    nm_bsp_reset();
    return M2M_SUCCESS;
}


sint8 nm_bsp_deinit(void) {
    HAL_GPIO_DeInit(WINC_CHIP_EN_PORT, WINC_CHIP_EN_PIN);
    HAL_GPIO_DeInit(WINC_RESET_N_PORT, WINC_RESET_N_PIN);
    return M2M_SUCCESS;
}


void nm_bsp_reset(void) {
    HAL_GPIO_WritePin(WINC_RESET_N_PORT, WINC_RESET_N_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(WINC_CHIP_EN_PORT, WINC_CHIP_EN_PIN, GPIO_PIN_RESET);
    nm_bsp_sleep(1U);
    HAL_GPIO_WritePin(WINC_CHIP_EN_PORT, WINC_CHIP_EN_PIN, GPIO_PIN_SET);
    nm_bsp_sleep(10U);
    HAL_GPIO_WritePin(WINC_RESET_N_PORT, WINC_RESET_N_PIN, GPIO_PIN_SET);
}


void nm_bsp_sleep(uint32 u32TimeMsec) {
    HAL_Delay(u32TimeMsec);
}


void nm_bsp_register_isr(tpfNmBspIsr pfIsr) {
    GPIO_InitTypeDef gpio_init = {0};

    WINC_IRQN_CLK_ENABLE();

    gpio_init.Pin = WINC_IRQN_PIN;
    gpio_init.Mode = GPIO_MODE_IT_FALLING;
    gpio_init.Pull = GPIO_PULLUP;

    HAL_GPIO_Init(WINC_IRQN_PORT, &gpio_init);

    gpfIsr = pfIsr;

    HAL_NVIC_SetPriority(WINC_IRQN_TYPE, 0, 0);
    HAL_NVIC_EnableIRQ(WINC_IRQN_TYPE);
}


void nm_bsp_interrupt_ctrl(uint8 u8Enable) {
    if (u8Enable) {
        HAL_NVIC_SetPriority(WINC_IRQN_TYPE, 0, 0);
        HAL_NVIC_EnableIRQ(WINC_IRQN_TYPE);
    } else {
        HAL_NVIC_DisableIRQ(WINC_IRQN_TYPE);
    }
}
