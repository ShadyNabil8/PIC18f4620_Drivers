/*
 * File:   dc_motor.c
 * Author: shady
 *
 * Created on May 17, 2023, 4:54 PM
 */

/* ----------------- Includes -----------------*/
#include "ecu_dc_motor.h"

Std_ReturnType motor_initialize(const motor_t *_motor)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_intialize(&(_motor->pin0));
        gpio_pin_intialize(&(_motor->pin1));
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType motor_stop(const motor_t *_motor)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_motor->pin0), GPIO_LOW);
        gpio_pin_write_logic(&(_motor->pin1), GPIO_LOW);
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType motor_rotate(const motor_t *_motor, rotation_t rotation)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (rotation == CLOCKWISE)
        {
            gpio_pin_write_logic(&(_motor->pin0), GPIO_HIGH);
            gpio_pin_write_logic(&(_motor->pin1), GPIO_LOW);
        }
        else
        {
            gpio_pin_write_logic(&(_motor->pin0), GPIO_LOW);
            gpio_pin_write_logic(&(_motor->pin1), GPIO_HIGH);
        }
        ret = E_OK;
    }
    return ret;
}