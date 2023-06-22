/*
 * File:   mcal_ISRs.c
 * Author: shady
 *
 * Created on June 20, 2023, 1:35 PM
 */
#include "mcal_ISRs.h"

// static void INTx_checker(void);
// static void RBx_checker(void);

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
    if (INTCON2bits.RBIP == INTERRUPTS_HIGH_PRIORITY)
    {
        if (previousRBxFlags != (PORTB & 0xF0))
        {
            // 10000000
            // 00000000
            if ((INTERRUPTS_RB4_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB4_ISR();
            }
            else
            { /* Nothing */
            }
            if ((INTERRUPTS_RB5_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB5_ISR();
            }
            else
            { /* Nothing */
            }
            if ((INTERRUPTS_RB6_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB6_ISR();
            }
            else
            { /* Nothing */
            }
            if ((INTERRUPTS_RB7_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB7_ISR();
            }
            else
            { /* Nothing */
            }
            previousRBxFlags = PORTB & 0xF0;
        }
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
    if (INTCON2bits.RBIP == INTERRUPTS_LOW_PRIORITY)
    {
        if (previousRBxFlags != (PORTB & 0xF0))
        {
            // 10000000
            // 00000000
            if ((INTERRUPTS_RB4_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB4_ISR();
            }
            else
            { /* Nothing */
            }
            if ((INTERRUPTS_RB5_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB5_ISR();
            }
            else
            { /* Nothing */
            }
            if ((INTERRUPTS_RB6_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB6_ISR();
            }
            else
            { /* Nothing */
            }
            if ((INTERRUPTS_RB7_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
            {
                volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
                RB7_ISR();
            }
            else
            { /* Nothing */
            }
            previousRBxFlags = PORTB & 0xF0;
        }
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
    if (previousRBxFlags != (PORTB & 0xF0))
    {
        // 10000000
        // 00000000
        if ((INTERRUPTS_RB4_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB4_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB5_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB5_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB6_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB6_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB7_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENEBLE == INTCONbits.RBIE) && (INTERRUPTS_ENEBLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB7_ISR();
        }
        else
        { /* Nothing */
        }
        previousRBxFlags = PORTB & 0xF0;
    }
}

#endif
