#ifndef __KEYPAD_H
#define __KEYPAD_H
#include "stm32f1xx_hal.h"

uint8_t GPIO_PortRead(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan();

#endif 

