#include "Keyboard.h"
#include "lcd.h"

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
	Delay(10);
	return(GPIOE -> idt & 0x00E0);
}


//Устанавливает нужные значения на  пинах вывода, сохраняет код нажатой кнопки
void ScanKey(void)
{
	uint16_t ActiveRow = (1<<1);
	while(ActiveRow & 0x001E)
	{
		GPIOE -> odt = (GPIOE -> odt & 0xFFE1) | ActiveRow;
		Delay(10);
		if(GPIOE -> idt & 0x00E0)
		{
			KeyCode  = GPIOE -> idt & 0x00E0;
			KeyCode |= GPIOE -> odt & 0x001E;
		}
		ActiveRow <<= 1;
	}
}


//Защита от прямого дребезга контактов
uint16_t SameKey(void)
{
	GPIOE -> odt = (GPIOE -> odt & 0xFFE1) | (KeyCode & 0x001E);
	Delay(10);
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
