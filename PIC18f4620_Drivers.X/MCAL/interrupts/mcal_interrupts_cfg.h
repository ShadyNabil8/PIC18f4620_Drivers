/*
 * File:   mcal_interrupts_cfg.h
 * Author: shady
 *
 * Created on June 20, 2023, 1:31 PM
 */

#ifndef MCAL_INTERRUPTS_CFG_H
#define MCAL_INTERRUPTS_CFG_H

/* ----------------- Includes -----------------*/
// #include "C:\Program Files\Microchip\xc8\v2.41\pic\include\proc\pic18f4620.h"
#include "..\GPIO\hal_gpio.h"

/* THIS IS VERY IMPORTANT TO MAKE PORTB BEHAVE AS DIGITAL PINS NOT ANALOG FOR ADC*/
//#pragma config PBADEN = OFF

/* ----------------- Macro Declarations -----------------*/
#define INTERRUPTS_ENABLE 1
#define INTERRUPTS_DISABLE 0
#define INTERRUPTS_PRIORITY_LEVELS_ENEBLE 1
#define INTERRUPTS_INTx_ENEBLE 0
#define INTERRUPTS_RBx_ENEBLE 0
#define INTERRUPTS_ADC_ENEBLE 0
#define INTERRUPTS_TIMER0_ENEBLE 1

/*INT0 is always high*/
#define INTERRUPTS_INT1_HIGH_PRIORITY 0
#define INTERRUPTS_INT2_HIGH_PRIORITY 0
#define INTERRUPTS_RBx_HIGH_PRIORITY 0
#define INTERRUPTS_ADC_HIGH_PRIORITY 0
#define INTERRUPTS_TIMER0_HIGH_PRIORITY 1
#define INTERRUPTS_USART_TX_HIGH_PRIORITY 1

/* ----------------- Macro Functions Declarations -----------------*/
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE

#define interrputs_priority_levels_enable() (RCONbits.IPEN = INTERRUPTS_ENABLE)
#define interrputs_priority_levels_disable() (RCONbits.IPEN = INTERRUPTS_DISABLE)
#define interrputs_high_priority_interrupt_eneble() (INTCONbits.GIEH = INTERRUPTS_ENABLE)
#define interrputs_high_priority_interrupt_disable() (INTCONbits.GIEH = INTERRUPTS_DISABLE)
#define interrputs_low_priority_interrupt_eneble() (INTCONbits.GIEL = INTERRUPTS_ENABLE)
#define interrputs_low_priority_interrupt_disable() (INTCONbits.GIEL = INTERRUPTS_DISABLE)

#else

#define interrputs_global_interrupt_eneble() (INTCONbits.GIE = INTERRUPTS_ENABLE)
#define interrputs_global_interrupt_disable() (INTCONbits.GIE = INTERRUPTS_DISABLE)
#define interrputs_peripheral_interrupt_enable() (INTCONbits.PEIE = INTERRUPTS_ENABLE)
#define interrputs_peripheral_interrupt_disable() (INTCONbits.PEIE = INTERRUPTS_DISABLE)

#endif

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    INTERRUPTS_LOW_PRIORITY,
    INTERRUPTS_HIGH_PRIORITY
} interrupts_priority_t;

typedef void (*InterruptHandler_t)(void);
/* ----------------- Software Interfaces Declarations -----------------*/

#endif /* MCAL_INTERRUPTS_CFG_H */
