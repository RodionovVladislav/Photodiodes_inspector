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
