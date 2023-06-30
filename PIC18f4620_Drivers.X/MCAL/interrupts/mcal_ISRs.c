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
#if INTERRUPTS_INTx_ENEBLE
    if ((INTERRUPTS_ENABLE == INTCONbits.INT0IE) && (INTERRUPTS_ENABLE == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else
    { /* Nothing */
    }
#if INTERRUPTS_INT1_HIGH_PRIORITY
    if ((INTCON3bits.INT1IP == INTERRUPTS_HIGH_PRIORITY) && (INTERRUPTS_ENABLE == INTCON3bits.INT1E) && (INTERRUPTS_ENABLE == INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else
    { /* Nothing */
    }
#endif
#if INTERRUPTS_INT2_HIGH_PRIORITY
    if ((INTCON3bits.INT2IP == INTERRUPTS_HIGH_PRIORITY) && (INTERRUPTS_ENABLE == INTCON3bits.INT2IE) && (INTERRUPTS_ENABLE == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else
    { /* Nothing */
    }
#endif
#endif

#if INTERRUPTS_RBx_ENEBLE
#if INTERRUPTS_RBx_HIGH_PRIORITY
    if (previousRBxFlags != (PORTB & 0xF0))
    {
        /*
         * HAAAAAAAAAAAAAAAAAAY
         * HAAAAAAAAAAAAAAAAAAY
         * HAAAAAAAAAAAAAAAAAAY
         * HAAAAAAAAAAAAAAAAAAY SHADY, MAKE A #DEFINE TO CHOSE THE RBx THAT YOU USED AND NEGLECT THE OTHERS
         * ALSO REMOVE (INTCON3bits.INT2IP == INTERRUPTS_HIGH_PRIORITY) && (INTERRUPTS_ENABLE == INTCON3bits.INT2IE) AND SO ON
         */
        if ((INTERRUPTS_RB4_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB4_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB5_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB5_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB6_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB6_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB7_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB7_ISR();
        }
        else
        { /* Nothing */
        }

        /* This line wil prevent thr nested interrupts(RBx) from occure */
        /* because when the other pin change its logic, the condition if (previousRBxFlags != (PORTB & 0xF0)) wil not be true*/
        previousRBxFlags = PORTB & 0xF0;
    }
#endif
#endif

#if INTERRUPTS_ADC_ENEBLE
#if INTERRUPTS_ADC_HIGH_PRIORITY
    if (INTERRUPTS_ENABLE == PIR1bits.ADIF)
    {
        ADC_ISR();
    }
    else
    { /* Nothing */
    }
#endif
#endif
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
#if INTERRUPTS_INTx_ENEBLE
#if !INTERRUPTS_INT1_HIGH_PRIORITY
    if ((INTCON3bits.INT1IP == INTERRUPTS_LOW_PRIORITY) && (INTERRUPTS_ENABLE == INTCON3bits.INT1E) && (INTERRUPTS_ENABLE == INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else
    { /* Nothing */
    }
#endif
#if !INTERRUPTS_INT2_HIGH_PRIORITY
    if ((INTCON3bits.INT2IP == INTERRUPTS_LOW_PRIORITY) && (INTERRUPTS_ENABLE == INTCON3bits.INT2IE) && (INTERRUPTS_ENABLE == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else
    { /* Nothing */
    }
#endif
#endif
#if INTERRUPTS_RBx_ENEBLE
#if !INTERRUPTS_RBx_HIGH_PRIORITY
    if (previousRBxFlags != (PORTB & 0xF0))
    {
        // 10000000
        // 00000000
        if ((INTERRUPTS_RB4_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB4_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB5_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB5_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB6_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB6_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB7_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB7_ISR();
        }
        else
        { /* Nothing */
        }
        /* This line wil prevent thr nested interrupts(RBx) from occure */
        /* because when the other pin change its logic, the condition if (previousRBxFlags != (PORTB & 0xF0)) wil not be true*/
        previousRBxFlags = PORTB & 0xF0;
    }
#endif
#endif

#if INTERRUPTS_ADC_ENEBLE
#if !INTERRUPTS_ADC_HIGH_PRIORITY
    if (INTERRUPTS_ENABLE == PIR1bits.ADIF)
    {
        ADC_ISR();
    }
    else
    { /* Nothing */
    }
#endif
#endif
}
#else
void __interrupt() InterruptManager(void)
{
#if INTERRUPTS_INTx_ENEBLE
    if ((INTERRUPTS_ENABLE == INTCONbits.INT0IE) && (INTERRUPTS_ENABLE == INTCONbits.INT0IF))
    {
        INT0_ISR(); /* External Interrupt 0 */
    }
    { /* Nothing */
    }
    if ((INTERRUPTS_ENABLE == INTCON3bits.INT1IE) && (INTERRUPTS_ENABLE == INTCON3bits.INT1IF))
    {
        INT1_ISR(); /* External Interrupt 0 */
    }
    { /* Nothing */
    }
    if ((INTERRUPTS_ENABLE == INTCON3bits.INT2IE) && (INTERRUPTS_ENABLE == INTCON3bits.INT2IF))
    {
        INT2_ISR(); /* External Interrupt 0 */
    }
    { /* Nothing */
    }
#endif

#if INTERRUPTS_RBx_ENEBLE
    if (previousRBxFlags != (PORTB & 0xF0))
    {
        // 10000000
        // 00000000
        if ((INTERRUPTS_RB4_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB4_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB5_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB5_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB6_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB6_ISR();
        }
        else
        { /* Nothing */
        }
        if ((INTERRUPTS_RB7_FLAG == (previousRBxFlags ^ (PORTB & 0xF0))) && (INTERRUPTS_ENABLE == INTCONbits.RBIE) && (INTERRUPTS_ENABLE == INTCONbits.RBIF))
        {
            volatile uint8_t dummy = PORTB; // Read PORTB to end mismatch condition
            RB7_ISR();
        }
        else
        { /* Nothing */
        }
        /* This line wil prevent thr nested interrupts(RBx) from occure */
        /* because when the other pin change its logic, the condition if (previousRBxFlags != (PORTB & 0xF0)) wil not be true*/
        previousRBxFlags = PORTB & 0xF0;
    }
#endif

#if INTERRUPTS_ADC_ENEBLE
    if (INTERRUPTS_ENABLE == PIR1bits.ADIF)
    {
        ADC_ISR();
    }
    else
    { /* Nothing */
    }
#endif
}
#endif
