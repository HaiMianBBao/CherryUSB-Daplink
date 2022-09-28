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
#define PIN_TDI        B1
#define PIN_TDO        B5
#define PIN_nRESET     B0
#define LED_CONNECTED  B2
#define LED_RUNNING    B15

#define DAP_CPU_CLOCK  0U

void dap_platform_init(void);
void dap_gpio_init(void);

static inline uint32_t dap_get_time_stamp(void)
{
    /*!< Your code */
}


