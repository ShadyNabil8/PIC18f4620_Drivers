/*
 * File:   hal_usart.c
 * Author: shady
 *
 * Created on July 26, 2023, 11:36 PM
 */

#include "hal_usart.h"

static Std_ReturnType USART_pins_init();
static void USART_baud_rate_init(const usart_t *_usart);
static void USART_serial_port_init(const usart_t *_usart);
static void USART_mode_init(const usart_t *_usart);
static void USART_bit_mode_init(const usart_t *_usart);
static void USART_rule_init(const usart_t *_usart);
static void USART_buffer_erase(uint8 *string, uint8 buffer_size);

Std_ReturnType USART_init(const usart_t *_usart)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _usart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= USART_pins_init();
        USART_baud_rate_init(_usart);
        USART_serial_port_init(_usart);
        USART_mode_init(_usart);
        USART_bit_mode_init(_usart);
        USART_rule_init(_usart);
    }
    return ret;
}

void USART_write_byte_blocking(uint8 data)
{
    USART_block_untill_shift_rig_is_empty();
    USART_start_transimission(data);
}
void USART_write_string_blocking(uint8 *str)
{
    while (*str != '\0')
    {
        USART_write_byte_blocking(*str++);
    }
    USART_write_byte_blocking('\0');
}
void USART_write_uint32_blocking(uint32 n)
{
    uint8 length = snprintf(NULL, 0, "%d", n);
    uint8 *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", n);
    USART_write_string_blocking(str);
}
void USART_read_byte_blocking(uint8 *data)
{
    USART_block_untill_reception_complete();
    *data = RCREG;
}
void USART_read_string_blocking(uint8 *string, uint8 buffer_size)
{
    USART_buffer_erase(string, buffer_size);
    uint8 index = 0;
    uint8 data;
    do
    {
        USART_read_byte_blocking(&data);
        string[index] = data;
        index++;
    } while (data != '\0');
}
void USART_read_uint32_blocking(uint32 *n)
{
    // n = atoi()
}
/************************************************************************************************/

static Std_ReturnType USART_pins_init()
{
    Std_ReturnType ret = E_OK;
    pin_config_t TX_pin =
        {
            .direction = GPIO_DIRECTION_INPUT,
            .port = GPIO_PORTC_INDEX,
            .pin = GPIO_PIN6};
    pin_config_t RX_pin =
        {
            .direction = GPIO_DIRECTION_INPUT,
            .port = GPIO_PORTC_INDEX,
            .pin = GPIO_PIN7};

    ret &= gpio_pin_direction_intialize(&TX_pin);
    ret &= gpio_pin_direction_intialize(&RX_pin);
    return ret;
}

static void USART_baud_rate_init(const usart_t *_usart)
{
    /* This function is suitable for 4MHZ */
    if (_usart->sync == USART_ASYNCHRONOUS_MODE)
    {
        USART_low_speed_baud_rate_enable();
        USART_16_bit_baud_rate_generator_enable();
        USART_set_SPBRG(25);
    }
    else
    {
    }
}
static void USART_serial_port_init(const usart_t *_usart)
{
    if (_usart->sync == USART_ASYNCHRONOUS_MODE)
    {
        USART_asynchronous_mode_enable();
        USART_enable();
    }
    else
    {
        /*code*/
    }
}
static void USART_mode_init(const usart_t *_usart)
{
    if (_usart->transimitter.state == USART_ENABLE)
    {
        if (_usart->transimitter.op_mode == USART_INTERRUPT_MODE)
        {
            interrputs_usartTX_enable();
        }
        else
        {
            interrputs_usartTX_disable();
        }
    }
    if (_usart->receiver.state == USART_ENABLE)
    {
        if (_usart->receiver.op_mode == USART_INTERRUPT_MODE)
        {
            interrputs_usartRX_enable();
        }
        else
        {
            interrputs_usartRX_disable();
        }
    }
}
static void USART_bit_mode_init(const usart_t *_usart)
{
    if (_usart->transimitter.state == USART_ENABLE)
    {
        if (_usart->transimitter.bit_mode == USART_8BITS_MODE)
        {
            USART_8_bit_transmission_enable();
        }
        else
        {
            USART_9_bit_transmission_enable();
        }
    }
    if (_usart->receiver.state == USART_ENABLE)
    {
        if (_usart->receiver.bit_mode == USART_8BITS_MODE)
        {
            USART_8_bit_reception_enable();
        }
        else
        {
            USART_9_bit_reception_enable();
        }
    }
}
static void USART_rule_init(const usart_t *usart)
{
    if (usart->transimitter.state == USART_ENABLE)
    {
        USART_transmit_enable();
    }
    if (usart->receiver.state == USART_ENABLE)
    {
        USART_enable_receiver();
    }
}
static void USART_buffer_erase(uint8 *string, uint8 buffer_size)
{
    for (uint8 i = 0; i < buffer_size; i++)
        string[i] = '\0';
}
