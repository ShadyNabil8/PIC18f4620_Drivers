/*
 * File:   ecu_button.c
 * Author: shady
 *
 * Created on May 16, 2023, 4:00 PM
 */
/* Section: includes */
#include "ecu_button.h"

Std_ReturnType button_initialize(const button_t *btn)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Do not forget the & */
        gpio_pin_direction_intialize(&(btn->attached_pin));
    }
    return ret;
}

Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state)
{
    Std_ReturnType ret = E_NOT_OK;
    if ((NULL == btn) || (NULL == btn_state))
    {
        ret = E_NOT_OK;
    }
    else
    {
        logic_t logic = GPIO_HIGH;
        gpio_pin_read_logic(&(btn->attached_pin), &logic);
        if (btn->btn_active == BUTTON_ACTIVE_HIGH)
        {
            if (GPIO_HIGH == logic)
            {
                /* Do not forget the(*) */
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                /* Do not forget the(*) */
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->btn_active == BUTTON_ACTIVE_LOW)
        {
            if (GPIO_HIGH == logic)
            {
                /* Do not forget the(*) */
                *btn_state = BUTTON_RELEASED;
            }
            else
            {
                /* Do not forget the(*) */
                *btn_state = BUTTON_PRESSED;
            }
        }
        else
        {
            /*NOTHING*/
        }
        ret = E_OK;
    }
    return ret;
}