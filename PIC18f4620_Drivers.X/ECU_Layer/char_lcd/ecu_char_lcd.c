/*
 * File:   ecu_char_lcd.c
 * Author: shady
 *
 * Created on June 16, 2023, 4:31 PM
 */

/*________ Encludes_________*/
#include "ecu_char_lcd.h"

/* Function declaration */
static Std_ReturnType lcd_4bit_send_4bits(const char_lcd_4bit_t *lcd, uint8 command);
static Std_ReturnType lcd_4bit_send_enable_signal(const char_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const char_lcd_4bit_t *lcd, uint8 row, uint8 column);

/* Function initialization */
Std_ReturnType lcd_4bit_intialize(const char_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        for (int i = 0; i < 4; i++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[i]));
        }

        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80); /* Go to the first address on the lcd (optional)*/
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_command(const char_lcd_4bit_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* the pin R\W on the lcd is connected to GND because of the 4-bit mode */

        /* pin_rs = LOW => write to the instruction regester */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);

        /* Writs data (last 4 bits) on the microcontroller pins */
        ret = lcd_4bit_send_4bits(lcd, (command >> 4));

        /* Let the lcd catch the data by detecting the falling edge on the en_pin */
        ret = lcd_4bit_send_enable_signal(lcd);

        /* Writs data (first 4 bits) on the microcontroller pins */
        ret = lcd_4bit_send_4bits(lcd, (command));

        /* Let the lcd catch the data by detecting the falling edge on the en_pin */
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}
static Std_ReturnType lcd_4bit_send_4bits(const char_lcd_4bit_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (int pin = 0; pin < _LCD_BIT_MODE; pin++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pin]), (command >> pin) & ((uint8)0x01));
        }
    }
    return ret;
}
static Std_ReturnType lcd_4bit_send_enable_signal(const char_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}
static Std_ReturnType lcd_4bit_set_cursor(const char_lcd_4bit_t *lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    switch (row)
    {
    case 0:
        ret = lcd_4bit_send_command(lcd, (0x80 + column));
        break; /* 0x00 -> Decimal : 0  */
    case 1:
        ret = lcd_4bit_send_command(lcd, (0xc0 + column));
        break; /* 0x40 -> Decimal : 64 */
    case 2:
        ret = lcd_4bit_send_command(lcd, (0x94 + column));
        break; /* 0x14 -> Decimal : 20 */
    case 3:
        ret = lcd_4bit_send_command(lcd, (0xd4 + column));
        break; /* 0x54 -> Decimal : 84 */
    default:
        break;
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_char_data(const char_lcd_4bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* the pin R\W on the lcd is connected to GND because of the 4-bit mode */

        /* pin_rs = HIGH => write to the data regester */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);

        /* Writs data (last 4 bits) on the microcontroller pins */
        ret = lcd_4bit_send_4bits(lcd, (data >> 4));

        /* Let the lcd catch the data by detecting the falling edge on the en_pin */
        ret = lcd_4bit_send_enable_signal(lcd);

        /* Writs data (first 4 bits) on the microcontroller pins */
        ret = lcd_4bit_send_4bits(lcd, (data));

        /* Let the lcd catch the data by detecting the falling edge on the en_pin */
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_char_data_pos(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string(const char_lcd_4bit_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 index = 0;
        while (str[index])
        {
            lcd_4bit_send_char_data(lcd, str[index]);
            index++;
        }
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string_pos(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_string(lcd, str);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_custom_char(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos);
Std_ReturnType lcd_4bit_send_uint8(const char_lcd_4bit_t *lcd, uint8 value)
{
    Std_ReturnType ret = E_OK;
    uint8 str[4];
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    { /* str should be an array of uint8 of size at least 4 */
        /* the maximum number in 8 bits is 3 digits */
        /* One extra car for '\0' */
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
        lcd_4bit_send_string(lcd,str);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_uint16(const char_lcd_4bit_t *lcd, uint16 value)
{
    Std_ReturnType ret = E_OK;
    uint8 str[6];
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    { /* str should be an array of uint8 of size at least 6 */
        /* the maximum number in 8 bits is 5 digits */
        /* One extra car for '\0' */
        memset(str, '\0', 6);
        sprintf(str, "%i", value);
        lcd_4bit_send_string(lcd,str);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_uint32(const char_lcd_4bit_t *lcd, uint32 value)
{
    Std_ReturnType ret = E_OK;
    uint8 str[11];
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    { /* str should be an array of uint8 of size at least 11 */
        /* the maximum number in 8 bits is 10 digits */
        /* One extra car for '\0' */
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
        lcd_4bit_send_string(lcd,str);
    }
    return ret;
}
