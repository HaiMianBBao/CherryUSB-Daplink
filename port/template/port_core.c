#include "port_common.h"
#include "ringbuffer.h"
static uint8_t rx_ch;
extern ring_buffer_t uart_ring_buffer;
extern ring_buffer_t cdc_ring_buffer;

void dap_platform_init(void)
{
    /*!< xxx */

    /*!< ringbuffer init */
    ring_buffer_init(&uart_ring_buffer);
    ring_buffer_init(&cdc_ring_buffer);
}

void dap_gpio_init(void)
{
    gpio_write(LED_CONNECTED, 1U);
    gpio_write(LED_RUNNING, 1U);
    gpio_set_mode(LED_CONNECTED, GPIO_OUTPUT_MODE);
    gpio_set_mode(LED_RUNNING, GPIO_OUTPUT_MODE);
}

void dap_uart_send_from_ringbuff(void)
{
    if (ring_buffer_is_empty(&cdc_ring_buffer))
    {
        return;
    }
    /*!< Send */
    uint16_t len = ring_buffer_num_items(&cdc_ring_buffer);
    char send_buffer[len];
    ring_buffer_dequeue_arr(&cdc_ring_buffer, send_buffer, len);
    /*!< Uart send */
}
