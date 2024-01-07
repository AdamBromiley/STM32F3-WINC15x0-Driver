#ifndef NM_BSP_STM32F3_H
#define NM_BSP_STM32F3_H


#include "bsp/include/nm_bsp.h"
#include "conf_winc.h"


#define NM_EDGE_INTERRUPT (1)

#define NM_DEBUG CONF_WINC_DEBUG
#define NM_BSP_PRINTF CONF_WINC_PRINTF


extern tpfNmBspIsr gpfIsr;


#endif