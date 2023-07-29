/*
 * File:   app.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "app.h"
char_lcd_4bit_t lcd;
usart_t usart;
uint8 data[20] = "welcode dhsd";
void main(void)
{
    lcd.lcd_rs.direction = GPIO_DIRECTION_OUTPUT;
    lcd.lcd_rs.logic = GPIO_LOW;
    lcd.lcd_rs.pin = GPIO_PIN0;
    lcd.lcd_rs.port = GPIO_PORTC_INDEX;
    lcd.lcd_en.direction = GPIO_DIRECTION_OUTPUT;
    lcd.lcd_en.logic = GPIO_LOW;
    lcd.lcd_en.pin = GPIO_PIN1;
    lcd.lcd_en.port = GPIO_PORTC_INDEX;

    for (int lcd_data_pins = 0; lcd_data_pins < 4; lcd_data_pins++)
    {
        lcd.lcd_data[lcd_data_pins].direction = GPIO_DIRECTION_OUTPUT;
        lcd.lcd_data[lcd_data_pins].logic = GPIO_LOW;
        lcd.lcd_data[lcd_data_pins].pin = (uint8)(lcd_data_pins + 2);
        lcd.lcd_data[lcd_data_pins].port = GPIO_PORTC_INDEX;
    }

    lcd_4bit_intialize(&lcd);
    usart.transimitter.state = USART_ENABLE;
    usart.transimitter.bit_mode = USART_8BITS_MODE;
    usart.transimitter.op_mode = USART_BLOCKING_MODE;
    usart.receiver.state = USART_ENABLE;
    usart.receiver.bit_mode = USART_8BITS_MODE;
    usart.receiver.op_mode = USART_BLOCKING_MODE;
    usart.sync = USART_ASYNCHRONOUS_MODE;
    USART_init(&usart);
    lcd_4bit_send_string(&lcd, data);
    //USART_write_string_blocking("WELCOME WORLD!");
    while (1)
    {
         __delay_ms(1000);
        USART_write_string_blocking("WELCOME WORLD!");
        __delay_ms(1000);
        USART_write_string_blocking("HELLO WORLD!");
        // USART_read_string_blocking(data);
        // lcd_4bit_send_string(&lcd, data);
        // __delay_ms(500);
    }
}
