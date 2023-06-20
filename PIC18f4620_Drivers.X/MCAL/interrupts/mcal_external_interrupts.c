/*
 * File:   mcal_external_interrupts.c
 * Author: shady
 *
 * Created on June 20, 2023, 1:32 PM
 */

#include "mcal_external_interrupts.h"

/* ------------------------------ HELPER FUNCTIONS ------------------------------*/
static InterruptHandler INT0_handler = NULL;
static InterruptHandler INT1_handler = NULL;
static InterruptHandler INT2_handler = NULL;

static Std_ReturnType interrupts_INTx_enable(const interrupts_INTx_t *INTx_obj);
static Std_ReturnType interrupts_INTx_disable(const interrupts_INTx_t *INTx_obj);
static Std_ReturnType interrupts_INTx_priority_init(const interrupts_INTx_t *INTx_obj);
static Std_ReturnType interrupts_INTx_edge_init(const interrupts_INTx_t *INTx_obj);
static Std_ReturnType interrupts_INTx_pin_init(const interrupts_INTx_t *INTx_obj);
static Std_ReturnType interrupts_INTx_clear_flag(const interrupts_INTx_t *INTx_obj);

static Std_ReturnType interrupts_INTx_ISR_init(const interrupts_INTx_t *INTx_obj);
// static Std_ReturnType interrupts_INT0_ISR_init(const interrupts_INTx_t *INTx_obj);
// static Std_ReturnType interrupts_INT1_ISR_init(const interrupts_INTx_t *INTx_obj);
// static Std_ReturnType interrupts_INT2_ISR_init(const interrupts_INTx_t *INTx_obj);

Std_ReturnType interrupts_INTx_init(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = interrupts_INTx_disable(INTx_obj);
        ret &= interrupts_INTx_edge_init(INTx_obj);
        ret &= interrupts_INTx_pin_init(INTx_obj);
        ret &= interrupts_INTx_clear_flag(INTx_obj);
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
        ret &= interrupts_INTx_priority_init(INTx_obj);
#endif
        ret &= interrupts_INTx_ISR_init(INTx_obj);
        ret &= interrupts_INTx_enable(INTx_obj);
    }
    return ret;
}
Std_ReturnType interrupts_INTx_deinit(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = interrupts_INTx_disable(INTx_obj);
    }
    return ret;
}

static Std_ReturnType interrupts_INTx_enable(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (INTx_obj->interrupt_src)
        {
        case INTERRUPTS_INT0:
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
            interrputs_priority_levels_enable();
            /* INT0 is always high priority */
            interrputs_high_priority_interrupt_eneble();
#else
            interrputs_global_interrupt_eneble();
            interrputs_peripheral_interrupt_enable();
#endif
            interrputs_INT0_enable();
            break;

        case INTERRUPTS_INT1:
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
            interrputs_priority_levels_enable();
            if (INTERRUPTS_HIGH_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_high_priority_interrupt_eneble();
            }
            else if (INTERRUPTS_LOW_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_low_priority_interrupt_eneble();
            }
            else
            {
                ret = E_NOT_OK;
            }
#else
            interrputs_global_interrupt_eneble();
            interrputs_peripheral_interrupt_enable();
#endif
            interrputs_INT1_enable();
            break;

        case INTERRUPTS_INT2:
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
            interrputs_priority_levels_enable();
            if (INTERRUPTS_HIGH_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_high_priority_interrupt_eneble();
            }
            else if (INTERRUPTS_LOW_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_low_priority_interrupt_eneble();
            }
            else
            {
                ret = E_NOT_OK;
            }
#else
            interrputs_global_interrupt_eneble();
            interrputs_peripheral_interrupt_enable();
#endif
            interrputs_INT2_enable();
            break;

        default:
            ret = E_NOT_OK;
            break;
        }
    }
    return ret;
}
static Std_ReturnType interrupts_INTx_disable(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (INTx_obj->interrupt_src)
        {
        case INTERRUPTS_INT0:
            interrputs_INT0_disable();
            break;

        case INTERRUPTS_INT1:
            interrputs_INT1_disable();
            break;

        case INTERRUPTS_INT2:
            interrputs_INT2_disable();
            break;

        default:
            ret = E_NOT_OK;
            break;
        }
    }
    return ret;
}
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
static Std_ReturnType interrupts_INTx_priority_init(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (INTx_obj->interrupt_src)
        {
        case INTERRUPTS_INT0:
            /* HIGH PRIORITY BY DEFAULT */
            break;

        case INTERRUPTS_INT1:
            if (INTERRUPTS_HIGH_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_INT1_apply_high_priority();
            }
            else if (INTERRUPTS_LOW_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_INT1_apply_low_priority();
            }
            else
            {
                ret = E_NOT_OK;
            }
            break;

        case INTERRUPTS_INT2:
            if (INTERRUPTS_HIGH_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_INT2_apply_high_priority();
            }
            else if (INTERRUPTS_LOW_PRIORITY == INTx_obj->interrupt_priority)
            {
                interrputs_INT2_apply_low_priority();
            }
            else
            {
                ret = E_NOT_OK;
            }
            break;

        default:
            ret = E_NOT_OK;
            break;
        }
    }
    return ret;
}
#endif
static Std_ReturnType interrupts_INTx_edge_init(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (INTx_obj->interrupt_src)
        {
        case INTERRUPTS_INT0:
            if (INTERRUPTS_RISING_EDGE == INTx_obj->interrupt_edge)
            {
                interrputs_INT0_apply_rising_edge();
            }
            else if (INTERRUPTS_FALLING_EDGE == INTx_obj->interrupt_edge)
            {
                interrputs_INT0_apply_falling_edge();
            }
            else
            {
                ret = E_NOT_OK;
            }
            break;

        case INTERRUPTS_INT1:
            if (INTERRUPTS_RISING_EDGE == INTx_obj->interrupt_edge)
            {
                interrputs_INT1_apply_rising_edge();
            }
            else if (INTERRUPTS_FALLING_EDGE == INTx_obj->interrupt_edge)
            {
                interrputs_INT1_apply_falling_edge();
            }
            else
            {
                ret = E_NOT_OK;
            }
            break;

        case INTERRUPTS_INT2:
            if (INTERRUPTS_RISING_EDGE == INTx_obj->interrupt_edge)
            {
                interrputs_INT2_apply_rising_edge();
            }
            else if (INTERRUPTS_FALLING_EDGE == INTx_obj->interrupt_edge)
            {
                interrputs_INT2_apply_falling_edge();
            }
            else
            {
                ret = E_NOT_OK;
            }
            break;

        default:
            ret = E_NOT_OK;
            break;
        }
    }
    return ret;
}
static Std_ReturnType interrupts_INTx_pin_init(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(&(INTx_obj->attached_pin));
    }
    return ret;
}
static Std_ReturnType interrupts_INTx_clear_flag(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (INTx_obj->interrupt_src)
        {
        case INTERRUPTS_INT0:
            interrputs_INT0_clear_flag();
            break;

        case INTERRUPTS_INT1:
            interrputs_INT1_clear_flag();
            break;

        case INTERRUPTS_INT2:
            interrputs_INT2_clear_flag();
            break;

        default:
            ret = E_NOT_OK;
            break;
        }
    }
    return ret;
}
// static Std_ReturnType interrupts_INT0_ISR_init(const interrupts_INTx_t *INTx_obj)
// {
// }
// static Std_ReturnType interrupts_INT1_ISR_init(const interrupts_INTx_t *INTx_obj)
// {
// }
// static Std_ReturnType interrupts_INT2_ISR_init(const interrupts_INTx_t *INTx_obj)
// {
// }
static Std_ReturnType interrupts_INTx_ISR_init(const interrupts_INTx_t *INTx_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == INTx_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (INTx_obj->interrupt_src)
        {
        case INTERRUPTS_INT0:
            INT0_handler = INTx_obj->INTx_handler;
            break;

        case INTERRUPTS_INT1:
            INT1_handler = INTx_obj->INTx_handler;
            break;

        case INTERRUPTS_INT2:
            INT2_handler = INTx_obj->INTx_handler;
            break;
        }
    }
    return ret;
}

void INT0_ISR(void)
{
    interrputs_INT0_clear_flag();
    if (INT0_handler)
    {
        INT0_handler();
    }
    else
    {
        /* Nothing*/
    }
}
void INT1_ISR(void)
{
    interrputs_INT1_clear_flag();
    if (INT1_handler)
    {
        INT1_handler();
    }
    else
    {
        /* Nothing*/
    }
}
void INT2_ISR(void)
{
    interrputs_INT2_clear_flag();
    if (INT2_handler)
    {
        INT2_handler();
    }
    else
    {
        /* Nothing*/
    }
}