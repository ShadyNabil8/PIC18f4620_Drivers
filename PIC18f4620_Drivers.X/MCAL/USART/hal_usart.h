/*
 * File:   hal_usart.h
 * Author: shady
 *
 * Created on July 26, 2023, 11:36 PM
 */

#ifndef HAL_USART_H
#define HAL_USART_H

#include "..\GPIO\hal_gpio.h"
#include "..\interrupts\mcal_interrupts_cfg.h"
#include "..\interrupts\mcal_peripheral_interrupts.h"
#include "hal_usart_cfg.h"

#define USART_SYNCHRONOUS_MODE 1
#define USART_ASYNCHRONOUS_MODE 0
#define USART_MASTER_MODE 1
#define USART_SLAVE_MODE 0
#define USART_BLOCKING_MODE 1
#define USART_INTERRUPT_MODE 0
#define USART_9BITS_MODE 1
#define USART_8BITS_MODE 0
#define USART_TX_MODE 1
#define USART_RX_MODE 0
#define USART_TX_RX_MODE 2
#define USART_ENABLE 1
#define USART_DISABLE 0
#define USART_SHIFT_REGISTER_FULL 0
#define USART_RECEIVER_EMPTY 0

#define USART_master_mode_enable() (TXSTAbits.CSRC = 1)
#define USART_slave_mode_enable() (TXSTAbits.CSRC = 0)
#define USART_9_bit_transmission_enable() (TXSTAbits.TX9 = 1)
#define USART_8_bit_transmission_enable() (TXSTAbits.TX9 = 0)
#define USART_9_bit_reception_enable() (RCSTAbits.RX9 = 1)
#define USART_8_bit_reception_enable() (RCSTAbits.RX9 = 0)
#define USART_transmit_enable() (TXSTAbits.TXEN = 1)
#define USART_transmit_disable() (TXSTAbits.TXEN = 0)
#define USART_enable_receiver() (RCSTAbits.CREN = 1)
#define USART_disable_receiver() (RCSTAbits.CREN = 0)
#define USART_synchronous_mode_enable() (TXSTAbits.SYNC = 1)
#define USART_asynchronous_mode_enable() (TXSTAbits.SYNC = 0)
#define USART_high_speed_baud_rate_enable() (TXSTAbits.BRGH = 1)
#define USART_low_speed_baud_rate_enable() (TXSTAbits.BRGH = 0)
#define USART_enable() (RCSTAbits.SPEN = 1)
#define USART_disable() (RCSTAbits.SPEN = 0)
#define USART_16_bit_baud_rate_generator_enable() (BAUDCONbits.BRG16 = 1)
#define USART_8_bit_baud_rate_generator_enable() (BAUDCONbits.BRG16 = 0)
#define USART_start_transimission(_data) (TXREG = _data)
#define USART_set_SPBRG(_data) (SPBRG = _data)
#define USART_block_untill_shift_rig_is_empty() \
    while (TXSTAbits.TRMT == USART_SHIFT_REGISTER_FULL)
#define USART_block_untill_reception_complete() \
    while (PIR1bits.RCIF == USART_RECEIVER_EMPTY)

typedef uint8 USART_sync_mode;
typedef uint8 USART_op_mode;
typedef uint8 USART_bit_mode;
typedef uint8 USART_rule;
typedef uint8 USART_state;

typedef struct
{
    USART_op_mode op_mode : 1;
    USART_bit_mode bit_mode : 1;
    USART_state state : 1;
    uint8 reserved : 5;
} usart_transimitter_t;

typedef struct
{
    USART_op_mode op_mode : 1;
    USART_bit_mode bit_mode : 1;
    USART_state state : 1;
    uint8 reserved : 5;
} usart_receiver_t;

typedef struct
{
    USART_rule rule : 1;
    USART_sync_mode sync : 1;
    uint8 reserved : 6;
    usart_transimitter_t transimitter;
    usart_receiver_t receiver;
} usart_t;

Std_ReturnType USART_init(const usart_t *_usart);
void USART_read_byte_blocking(uint8 *data);
void USART_read_string_blocking(uint8 *string, uint8 buffer_size);
void USART_read_uint32_blocking(uint32 *n);
void USART_read_byte_interrupted(uint8 *data);
void USART_write_byte_blocking(uint8 data);
void USART_write_string_blocking(uint8 *str);
void USART_write_uint32_blocking(uint32 n);
void USART_write_byte_interrupted(uint8 data);

#endif /* HAL_USART_H */
