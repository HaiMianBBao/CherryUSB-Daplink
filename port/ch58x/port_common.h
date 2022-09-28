#pragma once
#include <stdint.h>
#include "gpio.h"

#ifndef __STATIC_INLINE
#define __STATIC_INLINE __HIGH_CODE static inline
#endif

#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif


#define PIN_SWCLK_TCK  A15
#define PIN_SWDIO_TMS  A2
#define PIN_TDI        A0
#define PIN_TDO        A1
#define PIN_nRESET     A4
#define LED_CONNECTED  A9
#define LED_RUNNING    A11

#define UART_TX_PIN    B7  
#define UART_RX_PIN    B4

#define DAP_CPU_CLOCK  80000000U

void dap_platform_init(void);
void dap_gpio_init(void);

static inline uint32_t dap_get_time_stamp(void)
{
    extern uint32_t SYS_GetSysTickCnt(void);
    return SYS_GetSysTickCnt();
}
