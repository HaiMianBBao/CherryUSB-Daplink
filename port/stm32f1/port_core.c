#include <stdio.h>
#include <stdbool.h>
#include "port_common.h"
#include "ringbuffer.h"

GPIO_InitTypeDef GPIO_Init_Com;
static uint8_t rx_ch;
extern UART_HandleTypeDef huart2;
extern ring_buffer_t uart_ring_buffer;
extern ring_buffer_t cdc_ring_buffer;

volatile bool uart_dma_is_busy = false;

void usb_dc_low_level_init(void)
{
    /* Peripheral clock enable */
    __HAL_RCC_USB_CLK_ENABLE();
    /* USB interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
}

void dap_platform_init(void)
{
    /*!< Init dwt */
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;
    DWT_CYCCNT = (uint32_t)0u;
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;

    /*!< UART */
    HAL_UART_Receive_DMA(&huart2, (uint8_t *)&rx_ch, 1);
    ring_buffer_init(&uart_ring_buffer);
    ring_buffer_init(&cdc_ring_buffer);
}

void dap_gpio_init(void)
{
    gpio_set_mode(LED_CONNECTED, GPIO_OUTPUT_MODE);
    gpio_set_mode(LED_RUNNING, GPIO_OUTPUT_MODE);
    gpio_write(LED_CONNECTED, 1U);
    gpio_write(LED_RUNNING, 1U);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        ring_buffer_queue(&uart_ring_buffer, rx_ch);
        HAL_UART_Receive_DMA(&huart2, (uint8_t *)&rx_ch, 1);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if (uart_dma_is_busy == true)
        {
            uart_dma_is_busy = false;
        }
    }
}

char send_buffer[RING_BUFFER_SIZE];
void dap_uart_send_from_ringbuff(void)
{
    if (ring_buffer_is_empty(&cdc_ring_buffer))
    {
        return;
    }

    if (uart_dma_is_busy == false)
    {
        /*!< Send */
        uint16_t len = ring_buffer_num_items(&cdc_ring_buffer);
        ring_buffer_dequeue_arr(&cdc_ring_buffer, send_buffer, len);
        HAL_UART_Transmit_DMA(&huart2, (uint8_t *)send_buffer, len);
        uart_dma_is_busy = true;
    }
}