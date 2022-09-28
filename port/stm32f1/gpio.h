#pragma once
#include "stm32f1xx_hal.h"

enum
{
    GPIO_INPUT_MODE = 0, /*!< INPUT NO PULL */
    GPIO_OUTPUT_MODE,    /*!< OUTPUT MODE NO PULL */
    GPIO_INPUT_PP_MODE,  /*!< INPUT PULL UP */
};

#define GPIO_PIN_0   ((uint16_t)0x0001)   /* Pin 0 selected    */
#define GPIO_PIN_1   ((uint16_t)0x0002)   /* Pin 1 selected    */
#define GPIO_PIN_2   ((uint16_t)0x0004)   /* Pin 2 selected    */
#define GPIO_PIN_3   ((uint16_t)0x0008)   /* Pin 3 selected    */
#define GPIO_PIN_4   ((uint16_t)0x0010)   /* Pin 4 selected    */
#define GPIO_PIN_5   ((uint16_t)0x0020)   /* Pin 5 selected    */
#define GPIO_PIN_6   ((uint16_t)0x0040)   /* Pin 6 selected    */
#define GPIO_PIN_7   ((uint16_t)0x0080)   /* Pin 7 selected    */
#define GPIO_PIN_8   ((uint16_t)0x0100)   /* Pin 8 selected    */
#define GPIO_PIN_9   ((uint16_t)0x0200)   /* Pin 9 selected    */
#define GPIO_PIN_10  ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11  ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12  ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13  ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14  ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15  ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All ((uint16_t)0xFFFF) /* All pins selected */

#define B0  (0x80000000 | GPIO_PIN_0)
#define B1  (0x80000000 | GPIO_PIN_1)
#define B2  (0x80000000 | GPIO_PIN_2)
#define B3  (0x80000000 | GPIO_PIN_3)
#define B4  (0x80000000 | GPIO_PIN_4)
#define B5  (0x80000000 | GPIO_PIN_5)
#define B6  (0x80000000 | GPIO_PIN_6)
#define B7  (0x80000000 | GPIO_PIN_7)
#define B8  (0x80000000 | GPIO_PIN_8)
#define B9  (0x80000000 | GPIO_PIN_9)
#define B10 (0x80000000 | GPIO_PIN_10)
#define B11 (0x80000000 | GPIO_PIN_11)
#define B12 (0x80000000 | GPIO_PIN_12)
#define B13 (0x80000000 | GPIO_PIN_13)
#define B14 (0x80000000 | GPIO_PIN_14)
#define B15 (0x80000000 | GPIO_PIN_15)

#define C0  (0x40000000 | GPIO_PIN_0)
#define C1  (0x40000000 | GPIO_PIN_1)
#define C2  (0x40000000 | GPIO_PIN_2)
#define C3  (0x40000000 | GPIO_PIN_3)
#define C4  (0x40000000 | GPIO_PIN_4)
#define C5  (0x40000000 | GPIO_PIN_5)
#define C6  (0x40000000 | GPIO_PIN_6)
#define C7  (0x40000000 | GPIO_PIN_7)
#define C8  (0x40000000 | GPIO_PIN_8)
#define C9  (0x40000000 | GPIO_PIN_9)
#define C10 (0x40000000 | GPIO_PIN_10)
#define C11 (0x40000000 | GPIO_PIN_11)
#define C12 (0x40000000 | GPIO_PIN_12)
#define C13 (0x40000000 | GPIO_PIN_13)
#define C14 (0x40000000 | GPIO_PIN_14)
#define C15 (0x40000000 | GPIO_PIN_15)

#define A0  (0x20000000 | GPIO_PIN_0)
#define A1  (0x20000000 | GPIO_PIN_1)
#define A2  (0x20000000 | GPIO_PIN_2)
#define A3  (0x20000000 | GPIO_PIN_3)
#define A4  (0x20000000 | GPIO_PIN_4)
#define A5  (0x20000000 | GPIO_PIN_5)
#define A6  (0x20000000 | GPIO_PIN_6)
#define A7  (0x20000000 | GPIO_PIN_7)
#define A8  (0x20000000 | GPIO_PIN_8)
#define A9  (0x20000000 | GPIO_PIN_9)
#define A10 (0x20000000 | GPIO_PIN_10)
#define A11 (0x20000000 | GPIO_PIN_11)
#define A12 (0x20000000 | GPIO_PIN_12)
#define A13 (0x20000000 | GPIO_PIN_13)
#define A14 (0x20000000 | GPIO_PIN_14)
#define A15 (0x20000000 | GPIO_PIN_15)

static inline void gpio_set_mode(uint32_t pin, uint32_t mode)
{
    extern GPIO_InitTypeDef GPIO_Init_Com;
    GPIO_Init_Com.Pin = pin & 0xffff;
    GPIO_Init_Com.Speed = 0x3UL;
    if (mode == GPIO_INPUT_PP_MODE)
    {
        GPIO_Init_Com.Mode = GPIO_INPUT_MODE;
        GPIO_Init_Com.Pull = 1;
    }
    else
    {
        GPIO_Init_Com.Mode = mode;
        GPIO_Init_Com.Pull = 0;
    }
    if (pin & 0x80000000)
    {
        /*!< B */
        __HAL_RCC_GPIOB_CLK_ENABLE();
        HAL_GPIO_Init(GPIOB, &GPIO_Init_Com);
    }
    else if (pin & 0x40000000)
    {
        /*!< C */
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_Init(GPIOC, &GPIO_Init_Com);
    }
    else if (pin & 0x20000000)
    {
        /*!< A */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_Init(GPIOA, &GPIO_Init_Com);
    }
    else
    {
        // TODO:
    }
}


static inline void gpio_write(uint32_t pin, uint32_t pinstate)
{
    if (pin & 0x80000000)
    {
        HAL_GPIO_WritePin(GPIOB, (uint16_t)(pin & 0xffff), pinstate);
    }
    else if (pin & 0x40000000)
    {
        HAL_GPIO_WritePin(GPIOC, (uint16_t)(pin & 0xffff), pinstate);
    }
    else if (pin & 0x20000000)
    {
        HAL_GPIO_WritePin(GPIOA, (uint16_t)(pin & 0xffff), pinstate);
    }
}

static inline uint8_t gpio_read(uint32_t pin)
{
    if (pin & 0x80000000)
    {
        return HAL_GPIO_ReadPin(GPIOB, (uint16_t)(pin & 0xffff));
    }
    else if (pin & 0x40000000)
    {
        return HAL_GPIO_ReadPin(GPIOC, (uint16_t)(pin & 0xffff));
    }
    else if (pin & 0x20000000)
    {
        return HAL_GPIO_ReadPin(GPIOA, (uint16_t)(pin & 0xffff));
    }
    else
    {
        return 0;
    }
}