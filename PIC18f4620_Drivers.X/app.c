/*
 * File:   app.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "app.h"

led_t led1;
void INT0_function(void);
void ADC_function(void);
ADC_t adc;
volatile adc_result_t adc_result = 55;
ADC_channel_t channel = ADC_CHANNEL0;
void main(void)
{
    Std_ReturnType ret;

    adc.channel = ADC_CHANNEL0;
    adc.ADC_Handler = ADC_function;
    adc.priority = INTERRUPTS_LOW_PRIORITY;
    adc.pin.direction = GPIO_DIRECTION_INPUT;
    adc.pin.pin = GPIO_PIN0;
    adc.pin.port = GPIO_PORTA_INDEX;

    interrupts_INTx_t int0 =
        {
            .interrupt_edge = INTERRUPTS_RISING_EDGE,
            .interrupt_priority = INTERRUPTS_HIGH_PRIORITY,
            .attached_pin.direction = GPIO_DIRECTION_INPUT,
            .attached_pin.logic = GPIO_HIGH,
            .attached_pin.pin = GPIO_PIN0,
            .attached_pin.port = GPIO_PORTB_INDEX,
            .interrupt_src = INTERRUPTS_INT0,
            .INTx_handler = INT0_function

        };

    ret = interrupts_INTx_init(&int0);
    ret = adc_init(&adc);

    while (1)
    {

        ret = adc_read(&adc, NULL);
        __delay_ms(500);
    }
}

void INT0_function(void)
{
    Std_ReturnType ret = E_NOT_OK;
    // led_turn_toggle(&led1);
    // __delay_ms(3000);
    // led_turn_toggle(&led1);
    if (channel == ADC_CHANNEL0)
    {
        ret = adc_switch_channel(&adc, ADC_CHANNEL1);
        channel = ADC_CHANNEL1;
    }
    else
    {
        ret = adc_switch_channel(&adc, ADC_CHANNEL0);
        channel = ADC_CHANNEL0;
    }
}
void ADC_function(void)
{
    adc_result = ADC_RESULT;
}
