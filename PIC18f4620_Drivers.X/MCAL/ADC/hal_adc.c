/*
 * File:   hal_adc.c
 * Author: shady
 *
 * Created on June 30, 2023, 3:09 PM
 */

#include "hal_adc.h"
#if INTERRUPTS_ADC_ENEBLE
static InterruptHandler_t ADC_callback = NULL;
#endif
static Std_ReturnType adc_pin_init(const ADC_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_direction_intialize(&(adc_obj->pin));
    }
    return ret;
}

Std_ReturnType adc_init(const ADC_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_disable_module();
        ret = adc_pin_init(adc_obj);
        ADC_make_AN0_and_AN1_analog();
        ADC_apply_righ_justified();
        ADC_channel_setup(adc_obj->channel);

        /* By default VSS and VDD used*/
        ADC_voltage_refrence_configuration();

        /* These two configuration are suitable for 4MH frequency microcontroller.*/
        ADC_6_TAD();
        ADC_Fosc_2();

#if INTERRUPTS_ADC_ENEBLE
        interrputs_ADC_disable();
        interrputs_ADC_clear_flag();
        ADC_callback = adc_obj->ADC_Handler;

#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
        interrputs_ADC_enable();
        interrputs_ADC_priority(adc_obj->priority);
        
#if INTERRUPTS_ADC_HIGH_PRIORITY
        interrputs_high_priority_interrupt_eneble();
#else
        interrputs_low_priority_interrupt_eneble();
#endif

#else
        interrputs_global_interrupt_eneble();
        interrputs_peripheral_interrupt_enable();

#endif

#endif
        ADC_enable_module();
    }
    return ret;
}
Std_ReturnType adc_deinit(const ADC_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_disable_module();
    }
    return ret;
}
Std_ReturnType adc_read(const ADC_t *adc_obj, adc_result_t *result)
{
    Std_ReturnType ret = E_OK;
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        //*result = 0x00;
        ADC_start_convertion();

#if !INTERRUPTS_ADC_ENEBLE
        while (ADC_convertion_done() == ADC_CONVERSION_NOT_DONE)
            ;
        *result = (((adc_result_t)ADRESH) << 8) | (adc_result_t)ADRESL;
#endif
    }
    return ret;
}
Std_ReturnType adc_switch_channel(ADC_t *adc_obj, ADC_channel_t new_channel)
{
    Std_ReturnType ret = E_OK;
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        adc_obj->channel = new_channel;
        ADC_channel_setup(new_channel);
    }
    return ret;
}
#if INTERRUPTS_ADC_ENEBLE
void ADC_ISR(void)
{
    interrputs_ADC_clear_flag();
    if (ADC_callback)
    {
        ADC_callback();
    }
    else
    {
        /* Nothing*/
    }
}
#endif