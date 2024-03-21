/* Includes ------------------------------------------------------------------*/
#include "at32f403a_407_wk_config.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "lcd.h"
#include "Keyboard.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */
#define		Init									0
#define		Select								1
#define		Light									2
#define		Dark									3
#define		SelectConversion			4
#define		EnterValue						5
#define		WriteValueToFlash			6
#define		Conversion						7
#define		Comparison						8

char			LastLightValue[] = "";
char			LastDarkValue[] = "";
char			SymbolStrValue[20] = "";
char			DeviceStatus = 0;
char			ValueStatus = 0;
char 			Symbol = 0;
char			*endstr;
float			SymbolDecValue = 0;
uint16_t	LedArray[8] 	= {GPIO_PINS_8, GPIO_PINS_9, GPIO_PINS_10, GPIO_PINS_11, GPIO_PINS_12, GPIO_PINS_13, GPIO_PINS_14, GPIO_PINS_15};
uint16_t	RelayArray[8] = {GPIO_PINS_1, GPIO_PINS_2, GPIO_PINS_3, GPIO_PINS_4, GPIO_PINS_5, GPIO_PINS_6, GPIO_PINS_7, GPIO_PINS_8};
uint32_t 	Light_address = 0x080FF7F0;
uint32_t 	Dark_address 	= 0x080FF800;
uint64_t	HexVal = 0x0;
uint32_t 	H = 0;
uint32_t 	L = 0;

uint32_t 	i = 0;
uint32_t 	Arr[2];
uint32_t 	Hex = 0;
float			digfloat = 0;
float 		LightVal = 1;
float 		DarkVal = 1;
float			Value = 1;
uint8_t		WithdrawalStatus 	= 0;
uint8_t		LightDarkStatus  	= 2;
int8_t		ComparationStatus = 0;
uint8_t 	statusback = 0;
uint8_t		Sch31Array[][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
uint8_t 	limit_table[][2] = {{1, 1}, {2, 10}, {3, 100}, {4, 1}, {5, 10}};
float 		value 					 = 0;
char			str_value[] 		 = "";
int				r 							 = 0;
int 			m 							 = 0;
int     	sing  					 = 0;
uint8_t 	limit					 	 = 0;
/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */
void WritingValueToFlash(float value, uint32_t Address)
{
	flash_status_type status = FLASH_OPERATE_DONE;
	
	HexVal 		 = *(uint32_t*) &value;

	flash_unlock();
	
	status = flash_sector_erase(Address);
	
	if(status == FLASH_OPERATE_DONE)
	{
		status = flash_word_program(Address, HexVal);

		flash_lock();
		Delay(10);
	}
	else
	{
		flash_lock();
		while(1)
		{
			LCD_Clear();
			LCD_String("Ошибка записи");
			LCD_SetPos(0, 1);
			LCD_String("данных в память");
		}
		
	}
}


float ReadFlashValue(uint32_t Address)
{	
	//HexVal = *(uint32_t*)Address;
	digfloat = *(float*)Address;
	
	return digfloat;
}


void TakeTheValue(void)
{
	Sch31Array[8][3] = GPIOB -> idt_bit.idt1;
	Sch31Array[8][2] = GPIOB -> idt_bit.idt2;
	Sch31Array[8][1] = GPIOB -> idt_bit.idt3;
	Sch31Array[8][0] = GPIOB -> idt_bit.idt4;
	
	Sch31Array[7][3] = GPIOB -> idt_bit.idt5;
	Sch31Array[7][2] = GPIOB -> idt_bit.idt6;
	Sch31Array[7][1] = GPIOB -> idt_bit.idt7;
	Sch31Array[7][0] = GPIOB -> idt_bit.idt8;
	
	Sch31Array[6][3] = GPIOB -> idt_bit.idt9;
	Sch31Array[6][2] = GPIOB -> idt_bit.idt10;
	Sch31Array[6][1] = GPIOB -> idt_bit.idt11;
	Sch31Array[6][0] = GPIOB -> idt_bit.idt12;
	
	Sch31Array[5][3] = GPIOB -> idt_bit.idt13;
	Sch31Array[5][2] = GPIOB -> idt_bit.idt14;
	Sch31Array[5][1] = GPIOB -> idt_bit.idt15;
	Sch31Array[5][0] = GPIOC -> idt_bit.idt0;
	
	Sch31Array[4][3] = GPIOC -> idt_bit.idt1;
	Sch31Array[4][2] = GPIOC -> idt_bit.idt2;
	Sch31Array[4][1] = GPIOC -> idt_bit.idt3;
	Sch31Array[4][0] = GPIOC -> idt_bit.idt4;
	
	Sch31Array[3][3] = GPIOC -> idt_bit.idt5;
	Sch31Array[3][2] = GPIOC -> idt_bit.idt6;
	Sch31Array[3][1] = GPIOC -> idt_bit.idt7;
	Sch31Array[3][0] = GPIOC -> idt_bit.idt8;
	
	Sch31Array[2][0] = GPIOC -> idt_bit.idt9;
	
	Sch31Array[1][0] = GPIOC -> idt_bit.idt10;
	Sch31Array[1][1] = GPIOC -> idt_bit.idt11;
	Sch31Array[1][2] = GPIOC -> idt_bit.idt12;
	Sch31Array[1][3] = GPIOC -> idt_bit.idt13;
	
	Sch31Array[0][0] = GPIOC -> idt_bit.idt15;
	Sch31Array[0][1] = GPIOD -> idt_bit.idt0;
	Sch31Array[0][2] = GPIOD -> idt_bit.idt1;
	Sch31Array[0][3] = GPIOD -> idt_bit.idt2;
	
	value = 0;
	limit = 0;
	sing = 0;
	for(m = 8; m >= 0; m--)
	{
			for(r = 0; r <= 3; r++)
			{
					if(m >= 3){value += Sch31Array[m][r] * 1<<r;}
					if(m == 2){value += Sch31Array[m][r] * 1<<r;}
					if(m == 1){limit += Sch31Array[m][r] * 1<<r;}
					if(m == 0){sing  += Sch31Array[m][r] * 1<<r;}
			}
			if(m >= 3){value /= 10;}
	}
	
	for(r = 0; r <= 4; r++)
	{
			if(limit == limit_table[r][0])
			{
					value *= limit_table[r][1];
					break;
			}
	}
	
	if(sing == 11){value *= -1;}
}
/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  /* add user code begin 1 */

  /* add user code end 1 */

  /* system clock config. */
  wk_system_clock_config();

  /* config periph clock. */
  wk_periph_clock_config();

  /* init debug function. */
  wk_debug_config();

  /* nvic config. */
  wk_nvic_config();

  /* init tmr7 function. */
  wk_tmr7_init();

  /* init gpio function. */
  wk_gpio_config();

  /* add user code begin 2 */
	gpio_bits_set(GPIOA, GPIO_PINS_15);
  /* add user code end 2 */

  while(1)
  {
    /* add user code begin 3 */
		switch(DeviceStatus)
		{
//---------------------------------------------------------------------------------------------------------		
			case Init:
				LCD_Init();
				LCD_Clear();
			
				InitKeyboard();
			
				DeviceStatus = Select;
				break;
//---------------------------------------------------------------------------------------------------------			
			case Select:
				ScanKeyboard();
				Symbol = GetKey();
				if(WithdrawalStatus == 0)
				{
					LCD_Clear();
					LCD_String("Выберите изм.");
					LCD_SetPos(0,1);
					LCD_String("значение");
					Delay(1500);
					WithdrawalStatus = 3;
				}
				if(gpio_input_data_bit_read(GPIOB, GPIO_PINS_0))
				{
					if((WithdrawalStatus == 1) | (WithdrawalStatus == 3))
					{
						LCD_Clear();
						LCD_String("Световой I = ?");
						WithdrawalStatus = 2;
					}
					if(Symbol == '#')
					{
						DeviceStatus = Comparison;
						LightDarkStatus = 1;
						WithdrawalStatus = 0;
					}
				}
				else
				{
					if((WithdrawalStatus == 2) | (WithdrawalStatus == 3))
					{
						LCD_Clear();
						LCD_String("Темновой I = ?");
						WithdrawalStatus = 1;
					}
					if(Symbol == '#')
					{
						back:
						DeviceStatus = Comparison;
						LightDarkStatus = 0;
						WithdrawalStatus = 3;
					}
				}
				break;
//---------------------------------------------------------------------------------------------------------
			case Comparison:
				ScanKeyboard();
				Symbol = GetKey();
				if(gpio_input_data_bit_read(GPIOB, GPIO_PINS_0))
				{
					if((WithdrawalStatus == 0) | (WithdrawalStatus == 3))
					{
						LCD_Clear();
						LCD_String("Изм. значение");
						LCD_SetPos(0,1);
						LCD_String("должно быть: > ");
						WithdrawalStatus = 1;
						ComparationStatus = 1;
					}
				}
				else
				{
					if((WithdrawalStatus == 1) | (WithdrawalStatus == 3))
					{
						LCD_Clear();
						LCD_String("Изм. значение");
						LCD_SetPos(0,1);
						LCD_String("должно быть: < ");
						WithdrawalStatus = 0;
						ComparationStatus = -1;
					}
				}
				if(Symbol == '#')
				{
					if(LightDarkStatus == 1)
					{
						DeviceStatus = Light;
					}
					if(LightDarkStatus == 0)
					{
						DeviceStatus = Dark;
					}
				}
				if(Symbol == '.')
				{
					DeviceStatus  = Select;
				}
				break;
//---------------------------------------------------------------------------------------------------------				
			case Light:
				lback:
				statusback = Light;
				LightVal = ReadFlashValue(Light_address);
				sprintf(LastLightValue, "%f", LightVal);
				LCD_Clear();
				LCD_String("Пред. знач. IL:");
				LCD_SetPos(0,1);
				LCD_String(LastLightValue);
				Symbol = 0;
				while((Symbol != '#') & (Symbol != '.'))
				{
					ScanKeyboard();
					Symbol = GetKey();
					if(Symbol == '.')
					{
						goto back;
					}
				}
				LCD_Clear();
				LCD_String("Исп. пред. знач.");
				LCD_SetPos(0,1);
				LCD_String("Да: \"#\" Нет: \"*\"");
				Symbol = 0;
				while((Symbol != '#') & (Symbol != '.'))
				{
					ScanKeyboard();
					Symbol = GetKey();
					if(Symbol == '#')
					{
						DeviceStatus = SelectConversion;
					}
					if(Symbol == '.')
					{
						DeviceStatus = EnterValue;
						LCD_Clear();
						LCD_String("Введите значение");
						LCD_SetPos(0,1);
					}
					ValueStatus = Light;
				}
				break;
//---------------------------------------------------------------------------------------------------------						
			case Dark:
				dback:
				statusback = Dark;
				DarkVal = ReadFlashValue(Dark_address);
				sprintf(LastDarkValue, "%f", DarkVal);
				LCD_Clear();
				LCD_String("Пред. знач. ID:");
				LCD_SetPos(0,1);
				LCD_String(LastDarkValue);
				Symbol = 0;
				while((Symbol != '#') & (Symbol != '.'))
				{
					ScanKeyboard();
					Symbol = GetKey();
					if(Symbol == '.')
					{
						goto back;
					}
				}
				LCD_Clear();
				LCD_String("Исп. пред. знач.");
				LCD_SetPos(0,1);
				LCD_String("Да: \"#\" Нет: \"*\"");
				Symbol = 0;
				while((Symbol != '#') & (Symbol != '.'))
				{
					ScanKeyboard();
					Symbol = GetKey();
					if(Symbol == '#')
					{
						DeviceStatus = SelectConversion;
					}
					if(Symbol == '.')
					{
						DeviceStatus = EnterValue;
						LCD_Clear();
						LCD_String("Введите значение");
						LCD_SetPos(0,1);
					}
					ValueStatus = Dark;
				}
				break;
//---------------------------------------------------------------------------------------------------------						
			case SelectConversion:
				LCD_Clear();
				if(ValueStatus == Light)
				{
					LightVal = ReadFlashValue(Light_address);
					Value = LightVal;
					sprintf(LastLightValue, "%lf", LightVal);
					LCD_String("IL:");
					LCD_String(LastLightValue);
					ValueStatus = Light;
				}
				if(ValueStatus == Dark)
				{
					DarkVal = ReadFlashValue(Dark_address);
					Value = DarkVal;
					sprintf(LastDarkValue, "%lf", DarkVal);
					LCD_String("ID:");
					LCD_String(LastDarkValue);
					ValueStatus = Dark;
				}
				LCD_SetPos(0,1);
				LCD_String("запустите преобр");
				Symbol = 0;
				while(gpio_input_data_bit_read(GPIOE, GPIO_PINS_0) == 1)
				{
					ScanKeyboard();
					Symbol = GetKey();
					if(Symbol == '.')
					{
						if(statusback == Light){goto lback;}
						if(statusback == Light){goto dback;}
					}
				}
				DeviceStatus = Conversion;
				break;
//---------------------------------------------------------------------------------------------------------					
			case EnterValue:
				ScanKeyboard();
				Symbol = GetKey();
				if(Symbol == '#')
				{
					SymbolDecValue = strtod(SymbolStrValue, &endstr);
					
					DeviceStatus = WriteValueToFlash;
				}
				else
				{
					LCD_SendChar(Symbol);
					sprintf(SymbolStrValue, "%s%c", SymbolStrValue, Symbol);					
				}
				break;
//---------------------------------------------------------------------------------------------------------					
			case WriteValueToFlash:
				if(ValueStatus == Light)
				{
					WritingValueToFlash(SymbolDecValue, Light_address);
				}
				if(ValueStatus == Dark)
				{
					WritingValueToFlash(SymbolDecValue, Dark_address);
				}
				SymbolStrValue[0] = 0;
				
				DeviceStatus = SelectConversion;
				break;
//---------------------------------------------------------------------------------------------------------			
			case Conversion:
				gpio_bits_reset(GPIOA, GPIO_PINS_15);
				if(ComparationStatus == 1)
				{
					for(i = 0; i < 8; i++)
					{
						gpio_bits_set(GPIOA, RelayArray[i]);
						Delay(500);
						TakeTheValue();
						if(value >= Value)
						{
							gpio_bits_set(GPIOE, LedArray[i]);
						}
						else{gpio_bits_reset(GPIOE, LedArray[i]);}
						gpio_bits_reset(GPIOA, RelayArray[i]);
					}
				}
				
				if(ComparationStatus == -1)
				{
					for(i = 0; i < 8; i++)
					{
						gpio_bits_set(GPIOA, RelayArray[i]);
						Delay(500);
						TakeTheValue();
						if(value < Value)
						{
							gpio_bits_set(GPIOE, LedArray[i]);
						}
						else{gpio_bits_reset(GPIOE, LedArray[i]);}
						gpio_bits_reset(GPIOA, RelayArray[i]);
					}
				}
				DeviceStatus = 9;
				break;
			
			case 9:
				LCD_Clear();
				LCD_String("Преобразование");
				LCD_SetPos(0, 1);
				LCD_String("выполнено");
				Delay(1500);
				LCD_Clear();
				LCD_String("Продолжить: \"#\"");
				LCD_SetPos(0, 1);
				LCD_String("Новое знач: \"*\"");
				Symbol = 0;
				while((Symbol != '#') & (Symbol != '.'))
				{
					ScanKeyboard();
					Symbol = GetKey();
					if(Symbol == '#'){DeviceStatus = SelectConversion;}
					if(Symbol == '.'){DeviceStatus = Select;}
				}
				break;
		}
    /* add user code end 3 */
  }
}
