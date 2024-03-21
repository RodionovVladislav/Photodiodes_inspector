#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "at32f403a_407_wk_config.h"
#include "stdbool.h"

void InitKeyboard(void);
void ScanKeyboard(void);
uint8_t GetKey(void);
uint16_t FindKey(void);

#endif
