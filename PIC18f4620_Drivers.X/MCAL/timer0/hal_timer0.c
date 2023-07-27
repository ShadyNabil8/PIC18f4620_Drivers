/*
 * File:   hal_timer0.c
 * Author: shady
 *
 * Created on July 1, 2023, 8:02 PM
 */

/*
 ***********************Includes
 */
#include "hal_timer0.h"

/*
 ***********************ISRs
 */
#if INTERRUPTS_TIMER0_ENEBLE
static InterruptHandler_t timer0_callback = NULL;
#endif

/*
 *********************** Macro functions
 */

#define timer0_write_to_register(_value) \
    TMR0H = (_value) >> 8;               \
    TMR0L = (uint8)(_value);

// static Std_ReturnType timer0_write_to_register(timer0_t *_timer0)
// {
//     Std_ReturnType ret = E_OK;
//     if (NULL == _timer0)
//     {
//         ret = E_NOT_OK;
//     }
//     else
//     {
//         TMR0H = (_value) >> 8;
//         TMR0L = (uint8)(_value);
//     }

//     return ret;
// }

static uint16 timer0_register_val = 0;   /* As initialization */
static uint16 timer0_prescaller_val = 3; /* As initialization */

static flag_t is_positive_integer(sfloat32 val)
{
    uint32 truncated = (uint16)val;
    if ((val == truncated) && (val > 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static Std_ReturnType calculate_prescaller(timer0_t *_timer0)
{
    Std_ReturnType ret = E_OK;
    uint16 prescaller_i = 1;
    sfloat32 register_value = 0; /* As initialization */
    for (prescaller_i; prescaller_i <= 256; prescaller_i *= 2)
    {
        register_value = (sfloat32)((sfloat32)pow((sfloat64)2, (sfloat64)16) - (((sfloat32)(_timer0->time) * (sfloat32)(_timer0->frequency) * 1000) / (4 * (sfloat32)(prescaller_i))));
        // register_value = (sfloat32)((uint32)pow((sfloat64)2, (sfloat64)16) - ((_timer0->time * (_timer0->frequency) * 1000) / (4 * prescaller_i)));
        if (is_positive_integer(register_value))
        {
            timer0_prescaller_val = prescaller_i; /* for degugging */
            if (prescaller_i == 1)
            {
                timer0_prescaller_disable();
            }
            else
            {
                timer0_prescaller_enable();
                timer0_prescaller_configuration((uint8)(log2(prescaller_i) - 1));
            }
            /* We write to the register to count form this value */
            timer0_write_to_register((uint16)register_value);
            timer0_register_val = (uint16)register_value; /* for degugging */
            break;
        }
    }
    if (prescaller_i > 256)
    {
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType timer0_init(timer0_t *_timer0)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer0)
    {
        ret = E_NOT_OK;
    }
    else
    {
        timer0_disable();
        timer0_mode_configuration(_timer0->running_mode);
        timer0_bit_configuration(_timer0->register_bits);
        if (_timer0->running_mode == TIMER0_COUNTER_MODE)
            timer0_edge_configuration(_timer0->edge);

#if INTERRUPTS_TIMER0_ENEBLE
        interrputs_timer0_disable();
        interrputs_timer0_clear_flag();
        timer0_callback = _timer0->timer0_handler;
        interrputs_timer0_enable();
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
        interrputs_priority_levels_enable();
#if INTERRUPTS_TIMER0_HIGH_PRIORITY
        interrputs_high_priority_interrupt_eneble();
#else
        interrputs_low_priority_interrupt_eneble();
#endif
#endif
#endif
        ret = calculate_prescaller(_timer0);
        timer0_enable();
    }
    return ret;
}
Std_ReturnType timer0_deinit(timer0_t *_timer0)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer0)
    {
        ret = E_NOT_OK;
    }
    else
    {
    }

    return ret;
}
Std_ReturnType timer0_read_from_register(timer0_t *_timer0)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer0)
    {
        ret = E_NOT_OK;
    }
    else
    {
    }

    return ret;
}

#if INTERRUPTS_TIMER0_ENEBLE
void timer0_ISR(void)
{
    interrputs_timer0_clear_flag();
    timer0_write_to_register(timer0_register_val);
    if (timer0_callback)
    {
        timer0_callback();
    }
    else
    {
        /* Nothing*/
    }
}
#endif