#include "Keyboard.h"
#include "lcd.h"

//������ ��������� ��������
uint8_t		KeyState;
//������ ��� ������� ������
uint16_t	KeyCode;
//������ ��������� �������� ������
uint16_t	KeyValue;
//��������������� ��� ����������� ������
bool			KeyDown;
//��������������� ��� ������� ����� ������
bool			KeyNew;

//������� �������������
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


//������������� ������ �������� ��  ����� ������, ��������� ��� ������� ������
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


//������ �� ������� �������� ���������
uint16_t SameKey(void)
{
	GPIOE -> odt = (GPIOE -> odt & 0xFFE1) | (KeyCode & 0x001E);
	Delay(10);
	return((GPIOE -> idt & KeyCode) & 0x00E0);	
}


//���������� ���������� �������� ������ ��� ���������� �������� KeyCode � KeyTable, ������������� �����
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


//���������� ���� ������� ������
void ClearKey(void)
{
	KeyDown = 0;
}


//���������� ���������� �������� ������� ������
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


//������� ������������ ����������
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
