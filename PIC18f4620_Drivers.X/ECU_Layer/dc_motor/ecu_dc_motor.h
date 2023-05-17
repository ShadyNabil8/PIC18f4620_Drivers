/*
 * File:   dc_motor.h
 * Author: shady
 *
 * Created on May 17, 2023, 4:54 PM
 */

#ifndef DC_MOTOR_H
#define DC_MOTOR_H

/* ----------------- Includes -----------------*/
#include "ecu_dc_motor_cfg.h"
#include "..\..\MCAL\GPIO\hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define CLOCKWISE 0x00U
#define ANTICLOCKWISE 0x01U

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef uint8 rotation_t;

typedef struct
{
    pin_config_t pin0;
    pin_config_t pin1;
} motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType motor_initialize(const motor_t *_motor);
Std_ReturnType motor_stop(const motor_t *_motor);
Std_ReturnType motor_rotate(const motor_t *_motor, rotation_t rotation);


#endif /* DC_MOTOR_H */
