/*
 * File:   app.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "app.h"

void main(void)
{
    Std_ReturnType ret;
    pin_config_t PINC0 = {
        .port = GPIO_PORTC_INDEX,
        .pin = GPIO_PIN0,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = GPIO_HIGH};
    pin_config_t PINB0 = {
        .port = GPIO_PORTB_INDEX,
        .pin = GPIO_PIN0,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = GPIO_HIGH};
    //    Std_ReturnType ret = gpio_pin_direction_intialize(&pinA0);
    //    ret = gpio_pin_write_logic(&pinA0,GPIO_HIGH);

    ret = gpio_port_direction_intialize(GPIO_PORTB_INDEX, 0x00);
    ret = gpio_port_write_logic(GPIO_PORTB_INDEX, 0x00);
    ret = gpio_port_direction_intialize(GPIO_PORTC_INDEX, 0xFF);
    while (1)
    {
        logic_t l = GPIO_HIGH;
        gpio_pin_read_logic(&PINC0, &l);
        if (l == GPIO_HIGH)
        {
            gpio_pin_write_logic(&PINB0,GPIO_HIGH);
        }
        else
        {
            
            gpio_pin_write_logic(&PINB0,GPIO_LOW);
        }
    }
}
