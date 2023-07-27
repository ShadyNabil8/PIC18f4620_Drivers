/*
 * File:   app.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "app.h"

usart_t usart;

void main(void)
{
    usart.transimitter.bit_mode = USART_8BITS_MODE;
    usart.transimitter.op_mode = USART_BLOCKING_MODE;
    usart.transimitter.state = USART_ENABLE;
    usart.receiver.state = USART_DISABLE;
    usart.sync = USART_ASYNCHRONOUS_MODE;
    USART_init(&usart);

    while (1)
    {
        USART_write_uint32_blocking(1234);
        __delay_ms(500);
    }
}

