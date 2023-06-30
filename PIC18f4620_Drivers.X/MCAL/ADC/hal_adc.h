/*
 * File:   hal_adc.h
 * Author: shady
 *
 * Created on June 30, 2023, 3:09 PM
 */

#ifndef HAL_ADC_H
#define HAL_ADC_H

/* ----------------- Includes -----------------*/
#include "..\GPIO\hal_gpio.h"
#include "..\interrupts\mcal_interrupts_cfg.h"
#include "..\interrupts\mcal_peripheral_interrupts.h"
#include "hal_adc_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define ADC_CHANNEL0 (ADC_channel_t)0X00
#define ADC_CHANNEL1 (ADC_channel_t)0X01
#define ADC_CHANNEL2 (ADC_channel_t)0X02
#define ADC_CHANNEL3 (ADC_channel_t)0X03
#define ADC_CHANNEL4 (ADC_channel_t)0X04
#define ADC_CHANNEL5 (ADC_channel_t)0X05
#define ADC_CHANNEL6 (ADC_channel_t)0X06
#define ADC_CHANNEL7 (ADC_channel_t)0X07
#define ADC_CHANNEL8 (ADC_channel_t)0X08
#define ADC_CHANNEL9 (ADC_channel_t)0X09
#define ADC_CHANNEL10 (ADC_channel_t)0X0A
#define ADC_CHANNEL11 (ADC_channel_t)0X0B
#define ADC_CHANNEL12 (ADC_channel_t)0X0C

#define ADC_ENABLE 1
#define ADC_DISABLE 0
#define ADC_RIGHT_JUSTIFIED 1
#define ADC_LEFT_JUSTIFIED 0
#define ADC_VSS_VDD 0X00

#define ADC_6TAD 3
#define ADC_Fosc_BY_2 0

#define ADC_CONVERSION_NOT_DONE 1

#define ADC_RESULT (((adc_result_t)ADRESH) << 8) | (adc_result_t)ADRESL

/* ----------------- Macro Functions Declarations -----------------*/
#define ADC_start_convertion() (ADCON0bits.GO = 1)
#define ADC_convertion_done() (ADCON0bits.DONE)
#define ADC_enable_module() (ADCON0bits.ADON = ADC_ENABLE)
#define ADC_disable_module() (ADCON0bits.ADON = ADC_DISABLE)

/*
 * AN0 AN1 AN2 AN3 AN4 AN5 AN6 AN7 AN8 AN9 AN10 AN11 AN12
 * A   A   D   D   D   D   D   D   D   D   D     D    D
 */
#define ADC_make_AN0_and_AN1_analog() (ADCON1bits.PCFG = 0X0D)

#define ADC_apply_righ_justified() (ADCON2bits.ADFM = ADC_RIGHT_JUSTIFIED)
#define ADC_voltage_refrence_configuration() (ADCON1bits.VCFG = ADC_VSS_VDD)
#define ADC_channel_setup(_config) (ADCON0bits.CHS = _config)
#define ADC_Fosc_2() (ADCON2bits.ADCS = ADC_Fosc_BY_2)
#define ADC_6_TAD() (ADCON2bits.ACQT = ADC_6TAD)

/* ----------------- Data Type Declarations -----------------*/
typedef uint16 adc_result_t;
typedef uint8 ADC_channel_t;
typedef struct
{
#if INTERRUPTS_ADC_ENEBLE
    InterruptHandler_t ADC_Handler;
    interrupts_priority_t priority;
#endif
    ADC_channel_t channel;
    pin_config_t pin;
} ADC_t;
/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType adc_init(const ADC_t *adc_obj);
Std_ReturnType adc_deinit(const ADC_t *adc_obj);
Std_ReturnType adc_read(const ADC_t *adc_obj, uint16 *result);
Std_ReturnType adc_switch_channel(ADC_t *adc_obj, ADC_channel_t new_channel);

#endif /* HAL_ADC_H */
