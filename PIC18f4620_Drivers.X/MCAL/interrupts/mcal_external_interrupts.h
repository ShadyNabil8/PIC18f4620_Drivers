/*
 * File:   mcal_external_interrupts.h
 * Author: shady
 *
 * Created on June 20, 2023, 1:32 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPTS_H
#define MCAL_EXTERNAL_INTERRUPTS_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupts_cfg.h"

/* ----------------- Macro Declarations -----------------*/
/* ----------------- Macro Functions Declarations -----------------*/
#define interrputs_INT0_enable() (INTCONbits.INT0IE = INTERRUPTS_ENEBLE)
#define interrputs_INT0_disable() (INTCONbits.INT0IE = INTERRUPTS_DISABLE)
#define interrputs_INT0_clear_flag() (INTCONbits.INT0IF = INTERRUPTS_DISABLE)
#define interrputs_INT0_apply_rising_edge() (INTCON2bits.INTEDG0 = INTERRUPTS_RISING_EDGE)
#define interrputs_INT0_apply_falling_edge() (INTCON2bits.INTEDG0 = INTERRUPTS_FALLING_EDGE)

#define interrputs_INT1_enable() (INTCON3bits.INT1IE = INTERRUPTS_ENEBLE)
#define interrputs_INT1_disable() (INTCON3bits.INT1IE = INTERRUPTS_DISABLE)
#define interrputs_INT1_clear_flag() (INTCON3bits.INT1IF = INTERRUPTS_DISABLE)
#define interrputs_INT1_apply_rising_edge() (INTCON2bits.INTEDG1 = INTERRUPTS_RISING_EDGE)
#define interrputs_INT1_apply_falling_edge() (INTCON2bits.INTEDG1 = INTERRUPTS_FALLING_EDGE)

#define interrputs_INT2_enable() (INTCON3bits.INT2IE = INTERRUPTS_ENEBLE)
#define interrputs_INT2_disable() (INTCON3bits.INT2IE = INTERRUPTS_DISABLE)
#define interrputs_INT2_clear_flag() (INTCON3bits.INT2IF = INTERRUPTS_DISABLE)
#define interrputs_INT2_apply_rising_edge() (INTCON2bits.INTEDG2 = INTERRUPTS_RISING_EDGE)
#define interrputs_INT2_apply_falling_edge() (INTCON2bits.INTEDG2 = INTERRUPTS_FALLING_EDGE)

#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE

#define interrputs_INT1_apply_high_priority() (INTCON3bits.INT1IP = INTERRUPTS_HIGH_PRIORITY)
#define interrputs_INT1_apply_low_priority() (INTCON3bits.INT1IP = INTERRUPTS_LOW_PRIORITY)

#define interrputs_INT2_apply_high_priority() (INTCON3bits.INT2IP = INTERRUPTS_HIGH_PRIORITY)
#define interrputs_INT2_apply_low_priority() (INTCON3bits.INT2IP = INTERRUPTS_LOW_PRIORITY)

#endif

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    INTERRUPTS_INT0,
    INTERRUPTS_INT1,
    INTERRUPTS_INT2,
} interrupts_src_t;

typedef enum
{
    INTERRUPTS_FALLING_EDGE,
    INTERRUPTS_RISING_EDGE
} interrupts_edge_t;

typedef struct
{
    interrupts_src_t interrupt_src;
    interrupts_edge_t interrupt_edge;
    pin_config_t attached_pin;
    interrupts_priority_t interrupt_priority;
    InterruptHandler INTx_handler;
} interrupts_INTx_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType
interrupts_INTx_init(const interrupts_INTx_t *INTx_obj);
Std_ReturnType interrupts_INTx_deinit(const interrupts_INTx_t *INTx_obj);

#endif /* MCAL_EXTERNAL_INTERRUPTS_H */
