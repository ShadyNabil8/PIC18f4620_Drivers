/*
 * File:   mcal_peripheral_interrupts.h
 * Author: shady
 *
 * Created on June 30, 2023, 11:49 PM
 */

#ifndef MCAL_PERIPHERAL_INTERRUPTS_H
#define MCAL_PERIPHERAL_INTERRUPTS_H
#include "mcal_interrupts_cfg.h"

/******************** ADC ********************/
#define interrputs_ADC_enable() (PIE1bits.ADIE = INTERRUPTS_ENABLE)
#define interrputs_ADC_disable() (PIE1bits.ADIE = INTERRUPTS_DISABLE)
#define interrputs_ADC_clear_flag() (PIR1bits.ADIF = INTERRUPTS_DISABLE)
#define interrputs_ADC_priority(_PRIORITY) (IPR1bits.ADIP = _PRIORITY)

#endif /* MCAL_PERIPHERAL_INTERRUPTS_H */
