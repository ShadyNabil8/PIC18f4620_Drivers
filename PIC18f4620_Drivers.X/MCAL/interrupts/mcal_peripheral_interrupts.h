/*
 * File:   mcal_peripheral_interrupts.h
 * Author: shady
 *
 * Created on June 30, 2023, 11:49 PM
 */

#ifndef MCAL_PERIPHERAL_INTERRUPTS_H
#define MCAL_PERIPHERAL_INTERRUPTS_H
#include "mcal_interrupts_cfg.h"

/**************************************** ADC ******************************************/
#define interrputs_ADC_enable() (PIE1bits.ADIE = INTERRUPTS_ENABLE)
#define interrputs_ADC_disable() (PIE1bits.ADIE = INTERRUPTS_DISABLE)
#define interrputs_ADC_clear_flag() (PIR1bits.ADIF = INTERRUPTS_DISABLE)
#define interrputs_ADC_priority(_PRIORITY) (IPR1bits.ADIP = _PRIORITY)

/**************************************** TIMER0 ****************************************/
#define interrputs_timer0_enable() (INTCONbits.TMR0IE = INTERRUPTS_ENABLE)
#define interrputs_timer0_disable() (INTCONbits.TMR0IE = INTERRUPTS_DISABLE)
#define interrputs_timer0_clear_flag() (INTCONbits.TMR0IF = INTERRUPTS_DISABLE)
#define interrputs_timer0_priority(_PRIORITY) (INTCON2bits.TMR0IP = _PRIORITY)

/**************************************** USART ****************************************/
#define interrputs_usartTX_enable() (PIE1bits.TXIE = INTERRUPTS_ENABLE)
#define interrputs_usartTX_disable() (PIE1bits.TXIE = INTERRUPTS_DISABLE)
#define interrputs_usartTX_clear_flag() (PIR1bits.TXIF = INTERRUPTS_DISABLE)
#define interrputs_usartTX_priority(_PRIORITY) (IPR1bits.TXIP = _PRIORITY)
#define interrputs_usartRX_enable() (PIE1bits.RCIE = INTERRUPTS_ENABLE)
#define interrputs_usartRX_disable() (PIE1bits.RCIE = INTERRUPTS_DISABLE)
#define interrputs_usartRX_priority(_PRIORITY) (IPR1bits.RCIP = _PRIORITY)
#endif /* MCAL_PERIPHERAL_INTERRUPTS_H */
