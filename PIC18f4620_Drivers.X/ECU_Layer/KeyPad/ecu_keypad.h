/*
 * File:   ecu_keypad.h
 * Author: shady
 *
 * Created on May 20, 2023, 2:25 AM
 */

#ifndef ECU_KEYPAD_H
#define ECU_KEYPAD_H

/* Includes */
#include "ecu_keypad_cfg.h"
#include "..\..\MCAL\GPIO\hal_gpio.h"

/* Section: Macro Declarations */
#define KEYPAD_ROWS_NUMBERS 4
#define KEYPAD_COLUMNS_NUMBERS 4

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct
{
    pin_config_t rows_pins[KEYPAD_ROWS_NUMBERS];
    pin_config_t columns_pins[KEYPAD_COLUMNS_NUMBERS];
}keypad_t;

/* Section: Function Declarations */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);

#endif /* ECU_KEYPAD_H */
