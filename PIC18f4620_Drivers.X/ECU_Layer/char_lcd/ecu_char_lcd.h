/* 
 * File:   ecu_char_lcd.h
 * Author: shady
 *
 * Created on June 16, 2023, 4:31 PM
 */

#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H

/* ----------------- Includes -----------------*/
#include "ecu_char_lcd_cfg.h"
#include "..\..\MCAL\GPIO\hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define _LCD_CLEAR                               0X01
#define _LCD_RETURN_HOME                         0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF            0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON             0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF            0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON             0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT              0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT             0x14
#define _LCD_DISPLAY_SHIFT_LEFT                  0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                 0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define _LCD_8BIT_MODE_2_LINE                    0x38
#define _LCD_4BIT_MODE_2_LINE                    0x28
#define _LCD_CGRAM_START                         0x40
#define _LCD_DDRAM_START                         0x80

#define _LCD_BIT_MODE                            4

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}char_lcd_4bit_t;


/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType lcd_4bit_intialize(const char_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const char_lcd_4bit_t *lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const char_lcd_4bit_t *lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const char_lcd_4bit_t *lcd,uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_4bit_send_string(const char_lcd_4bit_t *lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, 
                                         const uint8 _chr[], uint8 mem_pos);
Std_ReturnType lcd_4bit_send_uint8(const char_lcd_4bit_t *lcd, uint8 value);
Std_ReturnType lcd_4bit_send_uint16(const char_lcd_4bit_t *lcd, uint16 value);
Std_ReturnType lcd_4bit_send_uint32(const char_lcd_4bit_t *lcd, uint32 value);

#endif	/* ECU_CHAR_LCD_H */

