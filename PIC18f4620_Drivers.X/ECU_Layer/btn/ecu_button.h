/*
 * File:   ecu_button.h
 * Author: shady
 *
 * Created on May 16, 2023, 4:00 PM
 */

#ifndef ECU_BUTTON_H
#define ECU_BUTTON_H

/* ----------------- Includes -----------------*/
#include "../../MCAL/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    BUTTON_PRESSED,
    BUTTON_RELEASED
} button_state_t;

typedef enum
{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
} button_active_t;

typedef struct
{
    port_index_t port;
    pin_posn_t pin;
    button_state_t btn_state;
    button_active_t btn_active;
} button_t;

/* ----------------- Function Declarations -----------------*/
Std_ReturnType button_initialize(const button_t *btn);
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif /* ECU_BUTTON_H */
