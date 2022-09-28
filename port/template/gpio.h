#pragma once
/*!< #include "xxx_xxx.h" */

enum
{
    GPIO_INPUT_MODE = 0, /*!< INPUT NO PULL */
    GPIO_OUTPUT_MODE,    /*!< OUTPUT MODE NO PULL */
    GPIO_INPUT_PP_MODE,  /*!< INPUT PULL UP */
};




/**
 * Please implement the following interfaces according to your own platform
 */
#define gpio_set_mode(pin, mode)
#define gpio_write(pin, pinstate)
#define gpio_read(pin)