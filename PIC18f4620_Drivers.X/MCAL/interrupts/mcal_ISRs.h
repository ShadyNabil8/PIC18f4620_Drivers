/*
 * File:   mcal_ISRs.h
 * Author: shady
 *
 * Created on June 20, 2023, 1:35 PM
 */

#ifndef MCAL_ISRS_H
#define MCAL_ISRS_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupts_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define INTERRUPTS_RB4_FLAG 0b00010000
#define INTERRUPTS_RB5_FLAG 0b00100000
#define INTERRUPTS_RB6_FLAG 0b01000000
#define INTERRUPTS_RB7_FLAG 0b10000000

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
extern volatile uint8 previousRBxFlags;

/* ----------------- Software Interfaces Declarations -----------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(void);
void RB5_ISR(void);
void RB6_ISR(void);
void RB7_ISR(void);
void ADC_ISR(void);
void timer0_ISR(void);

#endif /* MCAL_ISRS_H */
