/* 
 * File:   mcal_ISRs.h
 * Author: shady
 *
 * Created on June 20, 2023, 1:35 PM
 */

#ifndef MCAL_ISRS_H
#define	MCAL_ISRS_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupts_cfg.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

#endif	/* MCAL_ISRS_H */

