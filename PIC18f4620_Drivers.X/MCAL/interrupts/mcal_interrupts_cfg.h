/*
 * File:   mcal_interrupts_cfg.h
 * Author: shady
 *
 * Created on June 20, 2023, 1:31 PM
 */

#ifndef MCAL_INTERRUPTS_CFG_H
#define MCAL_INTERRUPTS_CFG_H

/* ----------------- Includes -----------------*/
//#include "C:\Program Files\Microchip\xc8\v2.41\pic\include\proc\pic18f4620.h"
#include "..\GPIO\hal_gpio.h"

/* THIS IS VERY IMPORTANT TO MAKE PORTB BEHAVE AS DIGITAL PINS NOT ANALOG FOR ADC*/
#pragma config PBADEN = OFF

/* ----------------- Macro Declarations -----------------*/
#define INTERRUPTS_ENEBLE 1
#define INTERRUPTS_DISABLE 0
#define INTERRUPTS_PRIORITY_LEVELS_ENEBLE 1

/* ----------------- Macro Functions Declarations -----------------*/
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE

#define interrputs_priority_levels_enable() (RCONbits.IPEN = INTERRUPTS_ENEBLE)
#define interrputs_priority_levels_disable() (RCONbits.IPEN = INTERRUPTS_DISABLE)
#define interrputs_high_priority_interrupt_eneble() (INTCONbits.GIEH = INTERRUPTS_ENEBLE)
#define interrputs_high_priority_interrupt_disable() (INTCONbits.GIEH = INTERRUPTS_DISABLE)
#define interrputs_low_priority_interrupt_eneble() (INTCONbits.GIEL = INTERRUPTS_ENEBLE)
#define interrputs_low_priority_interrupt_disable() (INTCONbits.GIEL = INTERRUPTS_DISABLE)

#else
#define interrputs_global_interrupt_eneble() (INTCONbits.GIE = INTERRUPTS_ENEBLE)
#define interrputs_global_interrupt_disable() (INTCONbits.GIE = INTERRUPTS_DISABLE)
#define interrputs_peripheral_interrupt_enable() (INTCONbits.PEIE = INTERRUPTS_ENEBLE)
#define interrputs_peripheral_interrupt_disable() (INTCONbits.PEIE = INTERRUPTS_DISABLE)

#endif

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    INTERRUPTS_LOW_PRIORITY,
    INTERRUPTS_HIGH_PRIORITY
} interrupts_priority_t;

typedef void (*InterruptHandler)(void);
/* ----------------- Software Interfaces Declarations -----------------*/

#endif /* MCAL_INTERRUPTS_CFG_H */
