/*
 * File:   ecu_keypad.c
 * Author: shady
 *
 * Created on May 20, 2023, 2:25 AM
 */
#include "ecu_keypad.h"

static const uint8 btn_values[KEYPAD_COLUMNS_NUMBERS][KEYPAD_COLUMNS_NUMBERS] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}};

Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _keypad_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (uint8 row_pin_i = 0; row_pin_i < KEYPAD_ROWS_NUMBERS; row_pin_i++)
        {
            gpio_pin_intialize(&(_keypad_obj->rows_pins[row_pin_i]));
        }
        for (uint8 columns_pin_i = 0; columns_pin_i < KEYPAD_COLUMNS_NUMBERS; columns_pin_i++)
        {
            gpio_pin_intialize(&(_keypad_obj->columns_pins[columns_pin_i]));
        }
    }
    return ret;
}

Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value)
{
    Std_ReturnType ret = E_OK;
    if ((NULL == _keypad_obj) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Ensure that all of the rows pins are low output */
        for (uint8 row_pin_i = 0; row_pin_i < KEYPAD_ROWS_NUMBERS; row_pin_i++)
        {
            gpio_pin_write_logic(&(_keypad_obj->rows_pins[row_pin_i]), GPIO_LOW);
        }
        /* Loop on the row pins*/
        uint8 keyPressed = 0;
        logic_t logic = GPIO_LOW;
        uint8 row_pin_i = 0;
        while (keyPressed == 0)
        {
            if (row_pin_i > 3)
            {
                row_pin_i = 0;
            }
            gpio_pin_write_logic(&(_keypad_obj->rows_pins[row_pin_i]), GPIO_HIGH);
            for (uint8 columns_pin_i = 0; columns_pin_i < KEYPAD_COLUMNS_NUMBERS; columns_pin_i++)
            {
                gpio_pin_read_logic(&(_keypad_obj->columns_pins[columns_pin_i]), &logic);
                if (logic == GPIO_HIGH)
                {
                    keyPressed = 1;
                    *value = btn_values[row_pin_i][columns_pin_i];
                    break;
                }
            }
            gpio_pin_write_logic(&(_keypad_obj->rows_pins[row_pin_i]), GPIO_LOW);
            row_pin_i++;
        }
    }
    return ret;
}