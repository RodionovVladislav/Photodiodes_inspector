#include "at32f403a_407_board.h"
#include "at32f403a_407_clock.h"
#include "lcd.h"

char string[] = "Enter value:";

//void mx_adc_clock_init(void)
//{
//  crm_adc_clock_div_set(CRM_ADC_DIV_6);
//}


void gpio_keyboard_config(void)
{
  gpio_init_type gpio_init_struct;

	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_1|GPIO_PINS_2|GPIO_PINS_3|GPIO_PINS_4|GPIO_PINS_5|GPIO_PINS_6|GPIO_PINS_7;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOE, &gpio_init_struct);
}


void gpio_led_config(gpio_pull_type gpio_pull)
{
  gpio_init_type gpio_led_init_struct;

	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_led_init_struct);

  gpio_led_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_led_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_led_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_led_init_struct.gpio_pins = GPIO_PINS_8|GPIO_PINS_9|GPIO_PINS_10|GPIO_PINS_11|GPIO_PINS_12|GPIO_PINS_13|GPIO_PINS_14|GPIO_PINS_15;
  gpio_led_init_struct.gpio_pull = gpio_pull;
	gpio_init(GPIOE, &gpio_led_init_struct);
}


int main(void)
{

	gpio_lcd_config();
	gpio_keyboard_config();
	
	LCD_Init();
	LCD_String(string);
	LCD_SetPos(0,1);

	
	

//  mx_adc_clock_init();

  while(1)
  {
		gpio_led_config(GPIO_PULL_UP);
		gpio_bits_set(GPIOE, GPIO_PINS_2);
		Delay(1000);
		gpio_bits_reset(GPIOE, GPIO_PINS_2);
		Delay(1000);
  }
}

