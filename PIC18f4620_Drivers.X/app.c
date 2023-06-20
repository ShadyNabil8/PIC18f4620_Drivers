/*
 * File:   app.c
 * Author: shady
 *
 * Created on May 9, 2023, 1:03 AM
 */

#include "app.h"

// button_state_t state = BUTTON_PRESSED;
// keypad_t keypad;
// uint8 val = 0;
// char_lcd_4bit_t lcd;
led_t led1;
led_t led2;
led_t led3;
void INT0_function(void);
void INT1_function(void);
void INT2_function(void);
void main(void)
{
    Std_ReturnType ret;

    // lcd.lcd_rs.direction = GPIO_DIRECTION_OUTPUT;
    // lcd.lcd_rs.logic = GPIO_LOW;
    // lcd.lcd_rs.pin = GPIO_PIN0;
    // lcd.lcd_rs.port = GPIO_PORTC_INDEX;

    // lcd.lcd_en.direction = GPIO_DIRECTION_OUTPUT;
    // lcd.lcd_en.logic = GPIO_LOW;
    // lcd.lcd_en.pin = GPIO_PIN1;
    // lcd.lcd_en.port = GPIO_PORTC_INDEX;

    // for (int lcd_data_pins = 0; lcd_data_pins < 4; lcd_data_pins++)
    // {
    //     lcd.lcd_data[lcd_data_pins].direction = GPIO_DIRECTION_OUTPUT;
    //     lcd.lcd_data[lcd_data_pins].logic = GPIO_LOW;
    //     lcd.lcd_data[lcd_data_pins].pin = (uint8)(lcd_data_pins + 2);
    //     lcd.lcd_data[lcd_data_pins].port = GPIO_PORTC_INDEX;
    // }

    // lcd_4bit_intialize(&lcd);
    // lcd_4bit_send_char_data(&lcd,'S');

    // for (int i = 0; i < 4; i++)
    // {
    //     keypad.rows_pins[i].direction = GPIO_DIRECTION_OUTPUT;
    //     keypad.rows_pins[i].logic = GPIO_LOW;
    //     keypad.rows_pins[i].pin = (uint8)i;
    //     keypad.rows_pins[i].port = GPIO_PORTD_INDEX;

    //     keypad.columns_pins[i].direction = GPIO_DIRECTION_INPUT;
    //     keypad.columns_pins[i].logic = GPIO_LOW;
    //     keypad.columns_pins[i].pin = (uint8)(i+4);
    //     keypad.columns_pins[i].port = GPIO_PORTD_INDEX;
    // };

    // keypad_initialize(&keypad);

    led1.port = GPIO_PORTC_INDEX;
    led1.pin = GPIO_PIN0;
    led1.led_status = LED_ON;
    led2.port = GPIO_PORTC_INDEX;
    led2.pin = GPIO_PIN1;
    led2.led_status = LED_ON;
    led3.port = GPIO_PORTC_INDEX;
    led3.pin = GPIO_PIN2;
    led3.led_status = LED_ON;
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
    interrupts_INTx_t int1 =
        {
            .interrupt_edge = INTERRUPTS_RISING_EDGE,
            .interrupt_priority = INTERRUPTS_LOW_PRIORITY,
            .attached_pin.direction = GPIO_DIRECTION_INPUT,
            .attached_pin.logic = GPIO_HIGH,
            .attached_pin.pin = GPIO_PIN1,
            .attached_pin.port = GPIO_PORTB_INDEX,
            .interrupt_src = INTERRUPTS_INT1,
            .INTx_handler = INT1_function

        };  
    interrupts_INTx_t int2 =
        {
            .interrupt_edge = INTERRUPTS_RISING_EDGE,
            .interrupt_priority = INTERRUPTS_HIGH_PRIORITY,
            .attached_pin.direction = GPIO_DIRECTION_INPUT,
            .attached_pin.logic = GPIO_HIGH,
            .attached_pin.pin = GPIO_PIN2,
            .attached_pin.port = GPIO_PORTB_INDEX,
            .interrupt_src = INTERRUPTS_INT2,
            .INTx_handler = INT2_function

        };  
    // button_t btn =
    //     {
    //         .port = GPIO_PORTD_INDEX,
    //         .pin = GPIO_PIN0,
    //         .btn_active = BUTTON_ACTIVE_LOW,
    //         .btn_state = BUTTON_PRESSED};
    // relay_t relay =
    //     {
    //         .pin = GPIO_PIN1,
    //         .port = GPIO_PORTD_INDEX,
    //         .relay_state = RELAY_CLOSED};

    // motor_t motor =
    //     {
    //         .pin0 =
    //             {
    //                 .direction = GPIO_DIRECTION_OUTPUT,
    //                 .logic = GPIO_LOW,
    //                 .pin = GPIO_PIN2,
    //                 .port = GPIO_PORTD_INDEX},
    //         .pin1 =
    //             {
    //                 .direction = GPIO_DIRECTION_OUTPUT,
    //                 .logic = GPIO_LOW,
    //                 .pin = GPIO_PIN3,
    //                 .port = GPIO_PORTD_INDEX}};
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    ret = interrupts_INTx_init(&int0);
    ret = interrupts_INTx_init(&int1);
    ret = interrupts_INTx_init(&int2);
    // ret = button_initialize(&btn);
    // ret = relay_initialize(&relay);
    // ret = motor_initialize(&motor);

    while (1)
    {
        // keypad_get_value(&keypad,&val);
        // ret = button_read_state(&btn, &state);
        // if (state == BUTTON_PRESSED)
        // {
        //     led_turn_on(&led1);
        //     relay_open(&relay);
        //     motor_rotate(&motor, CLOCKWISE);
        // }
        // else
        // {
        //     led_turn_off(&led1);
        //     relay_close(&relay);
        //     motor_rotate(&motor, ANTICLOCKWISE);
        // }
        // __delay_ms(500);
        // motor_stop(&motor);
        // __delay_ms(500);
        //led_turn_toggle(&led1);
        //__delay_ms(500);
    }
}

void INT0_function(void)
{
    led_turn_toggle(&led1);
     __delay_ms(500);
}
void INT1_function(void)
{
    led_turn_toggle(&led2);
     __delay_ms(500);
}
void INT2_function(void)
{
    led_turn_toggle(&led3);
     __delay_ms(500);
}