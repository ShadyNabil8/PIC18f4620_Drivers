/*
 * File:   ecu_relay.h
 * Author: shady
 *
 * Created on May 17, 2023, 12:59 PM
 */

#ifndef ECU_RELAY_H
#define ECU_RELAY_H

/* ----------------- Includes -----------------*/
#include "..\..\MCAL\GPIO\hal_gpio.h"
#include "ecu_relay_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define RELAY_OPEN 0x00U
#define RELAY_CLOSED 0x01U
/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef uint8 relay_state_t;

/*
typedef enum
{
    RELAY_OPEN,
    RELAY_CLOSED
}relay_state_t;
*/
typedef struct
{
    uint8 pin : 3;
    uint8 port : 3;
    uint8 relay_state : 1;
} relay_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType relay_initialize(const relay_t *_relay);
Std_ReturnType relay_open(const relay_t *_relay);
Std_ReturnType relay_close(const relay_t *_relay);

#endif /* ECU_RELAY_H */
