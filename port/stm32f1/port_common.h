#pragma once
#include <stdint.h>
#include "gpio.h"

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif

#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif

#define PIN_SWCLK_TCK  A4
#define PIN_SWDIO_TMS  A6
#define PIN_TDI        A1
#define PIN_TDO        A5
#define PIN_nRESET     A0
#define LED_CONNECTED  B7
#define LED_RUNNING    B15
#define DAP_CPU_CLOCK  72000000U



#define  DWT_CR      *(uint32_t*)0xE0001000
#define  DWT_CYCCNT  *(uint32_t*)0xE0001004
#define  DEM_CR      *(uint32_t*)0xE000EDFC
#define  DEM_CR_TRCENA       (1<<24)
#define  DWT_CR_CYCCNTENA    (1<<0)


void dap_platform_init(void);
void dap_gpio_init(void);

static inline uint32_t dap_get_time_stamp(void)
{
    return ((uint32_t)DWT_CYCCNT);
}
