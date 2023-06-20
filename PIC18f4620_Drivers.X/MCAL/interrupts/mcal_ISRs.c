/*
 * File:   mcal_ISRs.c
 * Author: shady
 *
 * Created on June 20, 2023, 1:35 PM
 */
#include "mcal_ISRs.h"
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
void __interrupt() InterruptManagerHigh(void)
{
    if ((INTERRUPTS_ENEBLE == INTCONbits.INT0IE) && (INTERRUPTS_ENEBLE == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else
    { /* Nothing */
    }
    if ((INTCON3bits.INT1IP == INTERRUPTS_HIGH_PRIORITY) && (INTERRUPTS_ENEBLE == INTCON3bits.INT1E) && (INTERRUPTS_ENEBLE == INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else
    { /* Nothing */
    }
    if ((INTCON3bits.INT2IP == INTERRUPTS_HIGH_PRIORITY) && (INTERRUPTS_ENEBLE == INTCON3bits.INT2IE) && (INTERRUPTS_ENEBLE == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else
    { /* Nothing */
    }
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
    if ((INTCON3bits.INT1IP == INTERRUPTS_LOW_PRIORITY) && (INTERRUPTS_ENEBLE == INTCON3bits.INT1E) && (INTERRUPTS_ENEBLE == INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else
    { /* Nothing */
    }
    if ((INTCON3bits.INT2IP == INTERRUPTS_LOW_PRIORITY) && (INTERRUPTS_ENEBLE == INTCON3bits.INT2IE) && (INTERRUPTS_ENEBLE == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else
    { /* Nothing */
    }
}
#else
void __interrupt() InterruptManager(void)
{
    if ((INTERRUPTS_ENEBLE == INTCONbits.INT0IE) && (INTERRUPTS_ENEBLE == INTCONbits.INT0IF))
    {
        INT0_ISR(); /* External Interrupt 0 */
    }
    { /* Nothing */
    }
    if ((INTERRUPTS_ENEBLE == INTCON3bits.INT1IE) && (INTERRUPTS_ENEBLE == INTCON3bits.INT1IF))
    {
        INT1_ISR(); /* External Interrupt 0 */
    }
    { /* Nothing */
    }
    if ((INTERRUPTS_ENEBLE == INTCON3bits.INT2IE) && (INTERRUPTS_ENEBLE == INTCON3bits.INT2IF))
    {
        INT2_ISR(); /* External Interrupt 0 */
    }
    { /* Nothing */
    }
}

#endif
