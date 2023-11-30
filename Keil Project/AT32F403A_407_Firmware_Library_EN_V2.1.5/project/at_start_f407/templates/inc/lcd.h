#ifndef LCD_H_
#define LCD_H_

#include "at32f403a_407.h"

#define D4_set						gpio_bits_set(GPIOD, GPIO_PINS_5)
#define D5_set						gpio_bits_set(GPIOD, GPIO_PINS_6)
#define D6_set						gpio_bits_set(GPIOD, GPIO_PINS_7)
#define D7_set						gpio_bits_set(GPIOD, GPIO_PINS_8)

#define D4_reset					gpio_bits_reset(GPIOD, GPIO_PINS_5)
#define D5_reset					gpio_bits_reset(GPIOD, GPIO_PINS_6)
#define D6_reset					gpio_bits_reset(GPIOD, GPIO_PINS_7)
#define D7_reset					gpio_bits_reset(GPIOD, GPIO_PINS_8)

#define LCD_Enable				gpio_bits_set(GPIOD, GPIO_PINS_3)
#define LCD_Disable				gpio_bits_reset(GPIOD, GPIO_PINS_3)

#define LCD_RegSel_Data		gpio_bits_set(GPIOD, GPIO_PINS_4)
#define LCD_RegSel_Ins		gpio_bits_reset(GPIOD, GPIO_PINS_4)


void gpio_lcd_config(void);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_String(char* str);
void LCD_SetPos(uint8_t x, uint8_t y);
void Delay(unsigned long ms);



#endif
