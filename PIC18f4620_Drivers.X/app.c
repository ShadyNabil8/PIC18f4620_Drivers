/*
 * File:   app.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "app.h"

button_state_t state = BUTTON_PRESSED;
 logic_t logic = GPIO_HIGH;
void main(void)
{
    Std_ReturnType ret;
    led_t led1 =
        {
            .port = GPIO_PORTA_INDEX,
            .pin = GPIO_PIN0,
            .led_status = LED_ON};

    /*pin_config_t pin =
    {
        .direction = GPIO_DIRECTION_INPUT,
        .logic = GPIO_HIGH,
        .port = GPIO_PORTD_INDEX,
        .pin = GPIO_PIN0
    };*/
    button_t btn =
        {
            .port = GPIO_PORTD_INDEX,
            .pin = GPIO_PIN0,
            .btn_active = BUTTON_ACTIVE_HIGH,
            .btn_state = BUTTON_PRESSED};

    ret = led_initialize(&led1);
    ret = button_initialize(&btn);

   
    while (1)
    {
        ret = button_read_state(&btn, &state);
        if (state == BUTTON_PRESSED)
        {
            led_turn_on(&led1);
        }
        else
        {
            led_turn_off(&led1);
        }
    }
}
