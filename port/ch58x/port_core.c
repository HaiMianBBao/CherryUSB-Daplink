#include "port_common.h"
#include "ringbuffer.h"
static uint8_t rx_ch;
extern ring_buffer_t uart_ring_buffer;
extern ring_buffer_t cdc_ring_buffer;

void dap_platform_init(void)
{
    gpio_write(UART_TX_PIN, 1);
    gpio_set_mode(UART_RX_PIN, GPIO_INPUT_PP_MODE);
    gpio_set_mode(UART_TX_PIN, GPIO_OUTPUT_MODE);
    UART0_DefInit();
    UART0_ByteTrigCfg(UART_1BYTE_TRIG);
    UART0_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
    PFIC_EnableIRQ(UART0_IRQn);

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
    UART0_SendString((uint8_t *)send_buffer, len);
}

__INTERRUPT
__HIGH_CODE
void UART0_IRQHandler(void)
{
    volatile uint8_t i;

    switch (UART0_GetITFlag())
    {
    case UART_II_LINE_STAT:
    {
        /*!< Line status error */
        UART0_GetLinSTA();
        break;
    }
    case UART_II_RECV_RDY:
        /*!< Data reaches the set trigger point */
        rx_ch = UART0_RecvByte();
        ring_buffer_queue(&uart_ring_buffer, rx_ch);
        break;
    case UART_II_RECV_TOUT:
        /*!< Receiving timeout, one frame data receiving is completed temporarily */
        break;
    case UART_II_THR_EMPTY:
        /*!< The sending buffer is empty, and you can continue sending */
        break;
    case UART_II_MODEM_CHG:
        break;
    default:
        break;
    }
}
