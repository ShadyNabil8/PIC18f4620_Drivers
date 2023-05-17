/*
 * File:   ecu_relay.c
 * Author: shady
 *
 * Created on May 17, 2023, 12:59 PM
 */
#include "ecu_relay.h"

Std_ReturnType relay_initialize(const relay_t *_relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_state,
            .pin = _relay->pin,
            .port = _relay->port};
        ret = gpio_pin_intialize(&pin);
    }
    return ret;
}

Std_ReturnType relay_open(const relay_t *_relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        logic_t logic = GPIO_LOW;
        pin_config_t pin = {
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_state,
            .pin = _relay->pin,
            .port = _relay->port};
        ret = gpio_pin_write_logic(&pin, logic);
    }
    return ret;
}

Std_ReturnType relay_close(const relay_t *_relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        logic_t logic = GPIO_HIGH;
        pin_config_t pin = {
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_state,
            .pin = _relay->pin,
            .port = _relay->port};
        ret = gpio_pin_write_logic(&pin, logic);
    }
    return ret;
}