/*
 * File:   ecu_led.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "ecu_led.h"

Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = 
        {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        gpio_pin_intialize(&pin);
    }
    return ret;
}

Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = 
        {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        gpio_pin_write_logic(&pin,GPIO_HIGH);
    }
    return ret;

}
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = 
        {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        gpio_pin_write_logic(&pin,GPIO_LOW);
    }
    return ret;


}

Std_ReturnType led_turn_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = 
        {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        gpio_pin_toggle_logic(&pin);
    }
    return ret;

}
