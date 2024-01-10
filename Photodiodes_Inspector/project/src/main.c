/* add user code begin Header */
/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f403a_407_wk_config.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "lcd.h"
#include "Keyboard.h"
#include "stdio.h" 
/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */
//Хранит состояние автомата
uint8_t		KeyState;
//Хранит код нажатой кнопки
uint16_t	KeyCode;
//Хранит символьно значение кнопки
uint16_t	KeyValue;
//Устанавливается при удерживании кнопки
bool			KeyDown;
//Устанавливается при нажатии новой кнопки
bool			KeyNew;

//Таблица перекодировки
uint8_t KeyTable[][2] = 
{
	{0x22, '1'},
	{0x42, '2'},
	{0x82, '3'},
	{0x24, '4'},
  {0x44, '5'},
	{0x84, '6'},
	{0x28, '7'},
	{0x48, '8'},
	{0x88, '9'},
	{0x30, '.'},
	{0x50, '0'},
	{0x90, '#'}
};


void InitKeyboard(void)
{
	GPIOE -> odt &= 0xFFE1;
	
	KeyState = 0;
	KeyCode = 0;
	KeyValue = 0;
	KeyDown = 0;
	KeyNew = 0;
}


uint16_t AnyKey(void)
{
	GPIOE -> odt |= 0x001E;
	return(GPIOE -> idt & 0x00E0);
}


//Устанавливает нужные значения на  пинах вывода, сохраняет код нажатой кнопки
void ScanKey(void)
{
	uint16_t ActiveRow = (1<<1);
	while(ActiveRow & 0x001E)
	{
		GPIOE -> odt = (GPIOE -> odt & 0xFFE1) | ActiveRow;
		if(GPIOE -> idt & 0x00E0)
		{
			KeyCode  = GPIOE -> idt & 0x00E0;
			KeyCode |= GPIOE -> odt & 0x001E;
			gpio_bits_set(GPIOD, GPIO_PINS_9);
			Delay(100);
			gpio_bits_reset(GPIOD, GPIO_PINS_9);
			Delay(100);
		}
		ActiveRow <<= 1;
	}
}


//Защита от прямого дребезга контактов
uint16_t SameKey(void)
{
	GPIOE -> odt = (GPIOE -> odt & 0xFFE1) | (KeyCode & 0x001E);
	return((GPIOE -> idt & KeyCode) & 0x00E0);
}


//Записывает символьное значение кнопки при совпадении значений KeyCode и KeyTable, устанавливает флаги
uint16_t FindKey(void)
{
	uint8_t index;
	for(index = 0; index < 12; index++)
	{
		if(KeyTable[index][0] == KeyCode)
		{
			KeyValue = KeyTable[index][1];
			KeyDown = 1;
			KeyNew = 1;
			return 1;
		}
	}
	return 0;
}


//Сбрасывает флаг нажатой кнопки
void ClearKey(void)
{
	KeyDown = 0;
}


//Возвращает символьное значение нажатой кнопки
uint8_t GetKey(void)
{
	if(KeyNew)
	{
		KeyNew =0;
		return KeyValue;
	}
	else
		return 0;
}


//Функция сканирования клавиатуры
void ScanKeyboard(void)
{
   switch (KeyState){
     case 0: 
       if (AnyKey()) {
         ScanKey();
         KeyState = 1;
       }
       break;

     case 1: 
       if (SameKey()) {
           FindKey();
           KeyState = 2;
       }
       else KeyState = 0;
       break;
     
     case 2: 
        if (SameKey()){}
        else KeyState = 3;
        break;
    
     case 3: 
       if (SameKey()) {
         KeyState = 2;
       }
       else {
         ClearKey();
         KeyState = 0;
       }
       break;
     
     default:
        break;
   }
   
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
char 		 	string[] = "Enter value:";
uint16_t 	IntIDTValue = 0;
char 		 	StrIDTValue[16] = "Nothing";
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
	LCD_Init();
	LCD_Clear();
	LCD_String(string);
	LCD_SetPos(0,1);
	
	InitKeyboard();
  /* add user code end 2 */

  while(1)
  {
    /* add user code begin 3 */

		ScanKeyboard();
		LCD_SendChar(GetKey());
//		gpio_bits_set(GPIOD, GPIO_PINS_9);
//		Delay(100);
//		gpio_bits_reset(GPIOD, GPIO_PINS_9);
//		Delay(100);
//		LCD_SendChar(GetKey());
//		Delay(100);
//		if(GPIOE -> idt & 0xE0)
//		{
//			IntIDTValue = GPIOE -> idt & 0x00E0;
//			sprintf(StrIDTValue, "%x", IntIDTValue);
//			LCD_String(StrIDTValue);
//		}
//		
//		if((GPIOE -> idt & 0x00E0) == 0x0060)
//		{
//			gpio_bits_set(GPIOD, GPIO_PINS_9);
//			Delay(100);
//		}
//		else
//			gpio_bits_reset(GPIOD, GPIO_PINS_9);
//		Delay(100);
		
    /* add user code end 3 */
  }
}
