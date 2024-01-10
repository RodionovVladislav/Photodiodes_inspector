#include "lcd.h"




void delay(void)
{
	uint16_t i;
	for(i = 0; i < 1000; i++)
	{
		
	}
}


void Delay(uint16_t ms)
{
	tmr_counter_value_set(TMR7,0);
	while(tmr_counter_value_get(TMR7) < ms);
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
	if(ch != 0)
	{
		LCD_Data((uint8_t) ch);
		delay();
	}
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
