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
#define BUTTON_RELEASED    0x00U
#define BUTTON_PRESSED     0x01U
#define BUTTON_ACTIVE_LOW  0x00U
#define BUTTON_ACTIVE_HIGH 0x01U

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef uint8 button_state_t;
typedef uint8 button_active_t;
/*
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
*/
typedef struct
{
    uint8 port : 3;
    uint8 pin : 3;
    uint8 btn_state : 1;
    uint8 btn_active : 1;
} button_t;

/* ----------------- Function Declarations -----------------*/
Std_ReturnType button_initialize(const button_t *btn);
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif /* ECU_BUTTON_H */
