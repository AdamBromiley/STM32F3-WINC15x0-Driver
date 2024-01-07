#include <stddef.h>

#include "stm32f3xx_hal.h"

#include "bsp/include/nm_bsp.h"
#include "bus_wrapper/include/nm_bus_wrapper.h"
#include "common/include/nm_common.h"
#include "conf_winc.h"


#define NM_BUS_MAX_TRX_SZ 256


tstrNmBusCapabilities egstrNmBusCapabilities = {NM_BUS_MAX_TRX_SZ};


static SPI_HandleTypeDef hspi;


sint8 nm_bus_init(void *pvinit) {
    hspi.Instance = SPI_INSTANCE;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi.Init.NSS = SPI_NSS_HARD_OUTPUT;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;

    if (HAL_SPI_Init(&hspi) != HAL_OK) {
        return M2M_ERR_BUS_FAIL;
    }

    nm_bsp_reset();
    nm_bsp_sleep(1U);
    return M2M_SUCCESS;
}


sint8 nm_bus_ioctl(uint8 u8Cmd, void *pvParameter) {
    switch(u8Cmd) {
        case NM_BUS_IOCTL_RW:
            tstrNmSpiRw *pstrParam = (tstrNmSpiRw *) pvParameter;
            return nm_spi_rw(pstrParam->pu8InBuf, pstrParam->pu8OutBuf, pstrParam->u16Sz);
        default:
            return M2M_ERR_BUS_FAIL;
    }
}


sint8 nm_bus_deinit(void) {
    HAL_SPI_DeInit(&hspi);
    return M2M_SUCCESS;
}


sint8 nm_bus_reinit(void *config) {
    nm_bus_deinit();
    return (nm_bus_init(config) != M2M_SUCCESS) ? M2M_ERR_BUS_FAIL : M2M_SUCCESS;
}


sint8 nm_bus_speed(uint8 level) {
    if ((level == HIGH) || (level == LOW)) {
        return M2M_SUCCESS;
    }

    return M2M_ERR_INVALID_ARG;
}


sint8 nm_spi_rw(uint8 *pu8Mosi, uint8 *pu8Miso, uint16 u16Sz) {
    uint8 dummy_byte = 0;
    uint8 receive_mode = 0;

    if (!pu8Mosi) {
        pu8Mosi = &dummy_byte;
        receive_mode = 1;
    } else if(!pu8Miso) {
        pu8Miso = &dummy_byte;
    } else {
        return M2M_ERR_BUS_FAIL;
    }

    for (uint16 i = 0; i < u16Sz; i++) {
        HAL_SPI_TransmitReceive(&hspi, pu8Mosi, pu8Miso, 1, HAL_MAX_DELAY);

        if (receive_mode) {
            pu8Miso++;
        } else {
            pu8Mosi++;
        }
    }

    return M2M_SUCCESS;
}