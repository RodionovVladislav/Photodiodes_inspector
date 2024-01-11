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
#include "stdlib.h"
#include "string.h"

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */
char 		 	Str[] = "Enter value:";
char			DeviceStatus = 0;
char 			Symbol = 0;
char			SymbolStrValue[20] = "";
char			*endstr;
float			SymbolDecValue = 0;



uint16_t 	IntIDTValue = 0;
char 		 	StrIDTValue[16] = "Next";
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
	
  /* add user code end 2 */

  while(1)
  {
    /* add user code begin 3 */
		switch(DeviceStatus){
			case 0:
				LCD_Init();
				LCD_Clear();
				LCD_String(Str);
				LCD_SetPos(0,1);

				InitKeyboard();
			
				DeviceStatus = 1;
				break;
			
			case 1:
				ScanKeyboard();
				Symbol = GetKey();
				if(Symbol == '#'){
					DeviceStatus = 2;
				}
				else{
					LCD_SendChar(Symbol);
					sprintf(SymbolStrValue, "%s%c", SymbolStrValue, Symbol);
					SymbolDecValue = strtof(SymbolStrValue, &endstr);
				}
				
				break;
				
			case 2:
				LCD_Clear();
				LCD_String(SymbolStrValue);
				LCD_SetPos(0,1);
				if(SymbolDecValue > 23)
				{
					LCD_String("Yes");
					sprintf(Str, "%f", SymbolDecValue);
					LCD_String(Str);
				}
				DeviceStatus = 1;
		}
    /* add user code end 3 */
  }
}
