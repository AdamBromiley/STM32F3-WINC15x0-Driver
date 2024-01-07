#include "stm32f3xx_hal.h"

#include "bsp/include/nm_bsp_stm32f3.h"
#include "conf_winc.h"


void EXTI3_IRQHandler(void)
{
    if (__HAL_GPIO_EXTI_GET_IT(WINC_IRQN_PIN)) {
        HAL_GPIO_EXTI_IRQHandler(WINC_IRQN_PIN);
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin) {
    if(gpio_pin == WINC_IRQN_PIN) {
        if (gpfIsr) {
            gpfIsr();
        }
    }
}