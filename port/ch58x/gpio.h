#pragma once
#include "CH58x_common.h"

enum
{
    GPIO_OUTPUT_MODE,   /*!< OUTPUT MODE NO PULL */
    GPIO_INPUT_MODE,    /*!< INPUT NO PULL */
    GPIO_INPUT_PP_MODE, /*!< INPUT PULL UP */
};

#define NO_PIN 0

#define A0  (GPIO_Pin_0)
#define A1  (GPIO_Pin_1)
#define A2  (GPIO_Pin_2)
#define A3  (GPIO_Pin_3)
#define A4  (GPIO_Pin_4)
#define A5  (GPIO_Pin_5)
#define A6  (GPIO_Pin_6)
#define A7  (GPIO_Pin_7)
#define A8  (GPIO_Pin_8)
#define A9  (GPIO_Pin_9)
#define A10 (GPIO_Pin_10)
#define A11 (GPIO_Pin_11)
#define A12 (GPIO_Pin_12)
#define A13 (GPIO_Pin_13)
#define A14 (GPIO_Pin_14)
#define A15 (GPIO_Pin_15)

#define B0  (0x80000000 | GPIO_Pin_0)
#define B1  (0x80000000 | GPIO_Pin_1)
#define B2  (0x80000000 | GPIO_Pin_2)
#define B3  (0x80000000 | GPIO_Pin_3)
#define B4  (0x80000000 | GPIO_Pin_4)
#define B5  (0x80000000 | GPIO_Pin_5)
#define B6  (0x80000000 | GPIO_Pin_6)
#define B7  (0x80000000 | GPIO_Pin_7)
#define B8  (0x80000000 | GPIO_Pin_8)
#define B9  (0x80000000 | GPIO_Pin_9)
#define B10 (0x80000000 | GPIO_Pin_10)
#define B11 (0x80000000 | GPIO_Pin_11)
#define B12 (0x80000000 | GPIO_Pin_12)
#define B13 (0x80000000 | GPIO_Pin_13)
#define B14 (0x80000000 | GPIO_Pin_14)
#define B15 (0x80000000 | GPIO_Pin_15)
#define B16 (0x80000000 | GPIO_Pin_16)
#define B17 (0x80000000 | GPIO_Pin_17)
#define B18 (0x80000000 | GPIO_Pin_18)
#define B19 (0x80000000 | GPIO_Pin_19)
#define B20 (0x80000000 | GPIO_Pin_20)
#define B21 (0x80000000 | GPIO_Pin_21)
#define B22 (0x80000000 | GPIO_Pin_22)
#define B23 (0x80000000 | GPIO_Pin_23)

#define writePinHigh(pin) ((pin & 0x80000000) ? GPIOB_SetBits(pin & 0x7FFFFFFF) : GPIOA_SetBits(pin))
#define writePinLow(pin) ((pin & 0x80000000) ? GPIOB_ResetBits(pin & 0x7FFFFFFF) : GPIOA_ResetBits(pin))
#define writePin(pin, level) ((level) ? writePinHigh(pin) : writePinLow(pin))
#define readPin(pin) (((pin & 0x80000000) ? GPIOB_ReadPortPin(pin & 0x7FFFFFFF) : GPIOA_ReadPortPin(pin)) ? 1 : 0)

#define gpio_set_mode(pin, mode)                                                                 \
    switch (mode)                                                                                \
    {                                                                                            \
    case GPIO_OUTPUT_MODE:                                                                       \
        ((pin & 0x80000000) ? (R32_PB_PD_DRV &= ~(pin & 0x7FFFFFFF)) : (R32_PA_PD_DRV &= ~pin)); \
        ((pin & 0x80000000) ? (R32_PB_DIR |= (pin & 0x7FFFFFFF)) : (R32_PA_DIR |= pin));         \
        break;                                                                                   \
    case GPIO_INPUT_MODE:                                                                        \
        ((pin & 0x80000000) ? (R32_PB_PD_DRV &= ~(pin & 0x7FFFFFFF)) : (R32_PA_PD_DRV &= ~pin)); \
        ((pin & 0x80000000) ? (R32_PB_PU &= ~(pin & 0x7FFFFFFF)) : (R32_PA_PU &= ~pin));         \
        ((pin & 0x80000000) ? (R32_PB_DIR &= ~(pin & 0x7FFFFFFF)) : (R32_PA_DIR &= ~pin));       \
        break;                                                                                   \
    case GPIO_INPUT_PP_MODE:                                                                     \
        ((pin & 0x80000000) ? (R32_PB_PD_DRV &= ~(pin & 0x7FFFFFFF)) : (R32_PA_PD_DRV &= ~pin)); \
        ((pin & 0x80000000) ? (R32_PB_PU |= (pin & 0x7FFFFFFF)) : (R32_PA_PU |= pin));           \
        ((pin & 0x80000000) ? (R32_PB_DIR &= ~(pin & 0x7FFFFFFF)) : (R32_PA_DIR &= ~pin));       \
        break;                                                                                   \
    default:                                                                                     \
        break;                                                                                   \
    }

#define gpio_write writePin
#define gpio_read readPin
