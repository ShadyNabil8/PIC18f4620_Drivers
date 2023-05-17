/*
 * File:   app.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "app.h"

button_state_t state = BUTTON_PRESSED;
void main(void)
{
    Std_ReturnType ret;
    led_t led1 =
        {
            .port = GPIO_PORTA_INDEX,
            .pin = GPIO_PIN0,
            .led_status = LED_ON};
    button_t btn =
        {
            .port = GPIO_PORTD_INDEX,
            .pin = GPIO_PIN0,
            .btn_active = BUTTON_ACTIVE_LOW,
            .btn_state = BUTTON_PRESSED};
    relay_t relay =
        {
            .pin = GPIO_PIN1,
            .port = GPIO_PORTD_INDEX,
            .relay_state = RELAY_CLOSED};
    ret = led_initialize(&led1);
    ret = button_initialize(&btn);
    ret = relay_initialize(&relay);

    while (1)
    {
        ret = button_read_state(&btn, &state);
        if (state == BUTTON_PRESSED)
        {
            led_turn_on(&led1);
            relay_open(&relay);
        }
        else
        {
            led_turn_off(&led1);
            relay_close(&relay);
        }
    }
}
