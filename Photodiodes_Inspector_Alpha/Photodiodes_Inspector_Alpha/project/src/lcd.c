#include "lcd.h"



unsigned char    Alphabet[118][2] =
{
    {'À', 0x41}, {'Á', 0xA0}, {'Â', 0x42}, {'Ã', 0xA1}, {'Ä', 0xE0}, {'Å', 0x45}, {'¨', 0xA2},
    {'à', 0x61}, {'á', 0xB2}, {'â', 0xB3}, {'ã', 0xB4}, {'ä', 0xE3}, {'å', 0x65}, {'¸', 0xB5},

    {'Æ', 0xA3}, {'Ç', 0xA4}, {'È', 0xA5}, {'É', 0xA6}, {'Ê', 0x4B}, {'Ë', 0xA7}, {'Ì', 0x4D},
    {'æ', 0xB6}, {'ç', 0xB7}, {'è', 0xB8}, {'é', 0xB9}, {'ê', 0xBA}, {'ë', 0xBB}, {'ì', 0xBC},

    {'Í', 0x48}, {'Î', 0x4F}, {'Ï', 0xA8}, {'Ð', 0x50}, {'Ñ', 0x43}, {'Ò', 0x54}, {'Ó', 0xA9},
    {'í', 0xBD}, {'î', 0x6F}, {'ï', 0xBE}, {'ð', 0x70}, {'ñ', 0x63}, {'ò', 0xBF}, {'ó', 0x79},

    {'Ô', 0xAA}, {'Õ', 0x58}, {'Ö', 0xE1}, {'×', 0xAB}, {'Ø', 0xAC}, {'Ù', 0xE2}, {'Ú', 0xAD},
    {'ô', 0xE4}, {'õ', 0xD5}, {'ö', 0xE5}, {'÷', 0xC0}, {'ø', 0xC1}, {'ù', 0xE6}, {'ú', 0xC2},

    {'Û', 0xAE}, {'Ü', 0x62}, {'Ý', 0xAF}, {'Þ', 0xB0}, {'ß', 0xB1},
    {'û', 0xC3}, {'ü', 0xC4}, {'ý', 0xC5}, {'þ', 0xC6}, {'ÿ', 0xC7},


    {'A', 0x41}, {'B', 0x42}, {'C', 0x43}, {'D', 0x44}, {'E', 0x45}, {'F', 0x46}, {'G', 0x47},
    {'a', 0x61}, {'b', 0x62}, {'c', 0x63}, {'d', 0x64}, {'e', 0x65}, {'f', 0x66}, {'g', 0x67},
    
    {'H', 0x48}, {'I', 0x49}, {'J', 0x4A}, {'K', 0x4B}, {'L', 0x4C}, {'M', 0x4D}, {'N', 0x4E},
    {'h', 0x68}, {'i', 0x69}, {'j', 0x6A}, {'k', 0x6B}, {'l', 0x6C}, {'m', 0x6D}, {'n', 0x6E}, 

    {'O', 0x4F}, {'P', 0x50}, {'Q', 0x51}, {'R', 0x52}, {'S', 0x53}, {'T', 0x54}, {'U', 0x55},
    {'o', 0x6F}, {'p', 0x70}, {'q', 0x71}, {'r', 0x72}, {'s', 0x73}, {'t', 0x74}, {'u', 0x75},
    
    {'V', 0x56}, {'W', 0x57}, {'X', 0x58}, {'Y', 0x59}, {'Z', 0x5A},
    {'v', 0x76}, {'w', 0x77}, {'x', 0x78}, {'y', 0x79}, {'z', 0x7A}
};


void delay(void)
{
	uint16_t i = 0;
	for(i = 0; i < 1000; i++)
	{
		
	}
}


void Delay(uint16_t ms)
{
	tmr_counter_value_set(TMR7,0);
	while(tmr_counter_value_get(TMR7) < ms);
}


void LCD_RunLine(char* line)
{	
	uint16_t s = 0;

	LCD_Clear();
	LCD_SetPos(0,0);
	
	for(s = 17; s != s - (sizeof(line) + 16); s--)
	{
		LCD_SetPos(s,0);
		LCD_String(line);
		Delay(200);
		LCD_Clear();
	}
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
	uint8_t    i = 0;
	uint8_t    w = 0;
  uint8_t    SymbolStatus = 1;

	
	while(str[i] != 0)
	{
		SymbolStatus = 1;
    for(w = 0; w < 118; w++)
    {
			if(str[i] == Alphabet[w][0])
      {
				LCD_SendChar(Alphabet[w][1]);
        SymbolStatus = 0;
      }
    }
    if(SymbolStatus)
    {
			LCD_SendChar(str[i]);
    }
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
