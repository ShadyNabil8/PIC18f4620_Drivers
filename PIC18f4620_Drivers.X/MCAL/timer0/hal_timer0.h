/*
 * File:   hal_timer0.h
 * Author: shady
 *
 * Created on July 1, 2023, 8:02 PM
 */

#ifndef HAL_TIMER0_H
#define HAL_TIMER0_H

/*
 *********************** Includes
 */
#include "..\GPIO\hal_gpio.h"
#include "..\interrupts\mcal_interrupts_cfg.h"
#include "..\interrupts\mcal_peripheral_interrupts.h"
#include "hal_timer0_cfg.h"
#include <math.h>

/*
 *********************** Macros
 */
#define TIMER0_ENABLE 1
#define TIMER0_DISABLE 0
#define TIMER0_8_BIT_REGISTER 1
#define TIMER0_16_BIT_REGISTER 0
#define TIMER0_TIMER_MODE 0
#define TIMER0_COUNTER_MODE 1
#define TIMER0_FALLING_EDGE 1
#define TIMER0_RISING_EDGE 0
#define TIMER0_PRESCALER_ENABLE 0
#define TIMER0_PRESCALER_DISABLE 1
#define TIMER0_PRESCALER_2 0X00
#define TIMER0_PRESCALER_4 0X01
#define TIMER0_PRESCALER_8 0X02
#define TIMER0_PRESCALER_16 0X03
#define TIMER0_PRESCALER_32 0X04
#define TIMER0_PRESCALER_64 0X05
#define TIMER0_PRESCALER_128 0X06
#define TIMER0_PRESCALER_256 0X07
#define TIMER0_PRESCALER_1 0X08

/*
 *********************** Macro functions
 */
#define timer0_enable() (T0CONbits.TMR0ON = TIMER0_ENABLE)
#define timer0_disable() (T0CONbits.TMR0ON = TIMER0_DISABLE)
#define timer0_bit_configuration(_cfg) (T0CONbits.T08BIT = _cfg)

/*
 * To select between counter mode and tomer mode
 */
#define timer0_mode_configuration(_cfg) (T0CONbits.T0CS = _cfg)

#define timer0_edge_configuration(_cfg) (T0CONbits.T0SE = _cfg)
#define timer0_prescaller_enable() (T0CONbits.PSA = TIMER0_PRESCALER_ENABLE)
#define timer0_prescaller_disable() (T0CONbits.PSA = TIMER0_PRESCALER_DISABLE)
#define timer0_prescaller_configuration(_cfg) (T0CONbits.T0PS = _cfg)

/*
 *********************** Data types definations
 */

typedef uint8 timer0_prescaller_t;

/*
 * falling or rising
 */
typedef uint8 timer0_edge_t;

/*
 * 8 or 16 bits
 */
typedef uint8 timer0_register_bits_t;

/*
 * Counter or timer
 */
typedef uint8 timer0_running_mode_t;

typedef uint16 timer0_time_t;
typedef uint8 timer0_oscillator_frequency_MHZ_t;

typedef struct
{
    timer0_running_mode_t running_mode;
    timer0_register_bits_t register_bits;
    timer0_edge_t edge;
    timer0_oscillator_frequency_MHZ_t frequency;
    timer0_time_t time;
#if INTERRUPTS_TIMER0_ENEBLE
    InterruptHandler_t timer0_handler;
#if INTERRUPTS_PRIORITY_LEVELS_ENEBLE
    interrupts_priority_t priority;
#endif
#endif
} timer0_t;

/*
 *********************** SW interfaces
 */

Std_ReturnType timer0_init(timer0_t *_timer0);
Std_ReturnType timer0_deinit(timer0_t *_timer0);
Std_ReturnType timer0_read_from_register(timer0_t *_timer0);
Std_ReturnType timer0_write_to_register(timer0_t *_timer0);
#endif /* HAL_TIMER0_H */
