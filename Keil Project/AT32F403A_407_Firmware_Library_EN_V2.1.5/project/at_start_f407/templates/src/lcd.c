#include "lcd.h"

void gpio_lcd_config(void)
{
  gpio_init_type gpio_init_struct;

	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_3|GPIO_PINS_4|GPIO_PINS_5|GPIO_PINS_6|GPIO_PINS_7|GPIO_PINS_8;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOD, &gpio_init_struct);
}


void delay(void)
{
	uint16_t i;
	for(i = 0; i < 10; i++)
	{
		
	}
}


void Delay(unsigned long ms)
{
	unsigned long k = 0;
	unsigned long a = 0;
	
	k = ms*2800;
	while(a < k)
	{
		a++;
	}
	a = 0;
}


void LCD_WriteData(uint8_t data)
{
	if(((data>>3) & 0x01) == 1){D7_set;} else{D7_reset;}
	if(((data>>2) & 0x01) == 1){D6_set;} else{D6_reset;}
	if(((data>>1) & 0x01) == 1){D5_set;} else{D5_reset;}
	if((data & 0x01) == 1){D4_set;} else{D4_reset;}
}


void LCD_Command(uint8_t data)
{
	LCD_RegSel_Ins;
	delay();
	LCD_WriteData(data >> 4);
	LCD_Enable;
	delay();
	LCD_Disable;
	LCD_WriteData(data);
	LCD_Enable;
	delay();
	LCD_Disable;
}


void LCD_Data(uint8_t data)
{
	LCD_RegSel_Data;
	delay();
	LCD_WriteData(data >> 4);
	LCD_Enable;
	delay();
	LCD_Disable;
	LCD_WriteData(data);
	LCD_Enable;
	delay();
	LCD_Disable;
}


void LCD_Clear(void)
{
	LCD_Command(0x01);
	Delay(2);
}


void LCD_SendChar(char ch)
{
	LCD_Data((uint8_t) ch);
	delay();
}


void LCD_String(char* str)
{
	uint8_t i = 0;
	while (str[i] != 0)
	{
		LCD_Data(str[i]);
		delay();
		i++;
	}
}


void LCD_SetPos(uint8_t x, uint8_t y)
{
	switch(y)
	{
		case 0:
			LCD_Command(x|0x80);
			Delay(1);
			break;
		case 1:
			LCD_Command((0x40+x)|0x80);
			Delay(1);
			break;
	}
}


void LCD_Init(void)
{
	Delay(40);
	LCD_RegSel_Ins;
	delay();
	
	LCD_WriteData(3);
	LCD_Enable;
	delay();
	LCD_Disable;
	Delay(1);
	
	LCD_WriteData(3);
	LCD_Enable;
	delay();
	LCD_Disable;
	Delay(1);
	
	LCD_WriteData(3);
	LCD_Enable;
	delay();
	LCD_Disable;
	Delay(1);
	
	
	LCD_Command(0x28);
	Delay(2);
	LCD_Command(0x0F);
	Delay(2);
	LCD_Command(0x01);
	Delay(2);
	LCD_Command(0x06);
	Delay(2);
	LCD_Command(0x02);
	Delay(2);
	
}
