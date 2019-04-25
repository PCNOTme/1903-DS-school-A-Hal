#ifndef __KEYPAD_H
#define __KEYPAD_H
#include "stm32f1xx_hal.h"

#define KEY_PASG_PORT  GPIOD
#define KEYPAD_L1  GPIO_PIN_0
#define KEYPAD_L2  GPIO_PIN_1
#define KEYPAD_L3  GPIO_PIN_2
#define KEYPAD_L4  GPIO_PIN_3

#define KEY_BIT_PORT  GPIOD
#define KEYPAD_R1  GPIO_PIN_4
#define KEYPAD_R2  GPIO_PIN_5
#define KEYPAD_R3  GPIO_PIN_6
#define KEYPAD_R4  GPIO_PIN_7

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


void Key_Logic(void);
void KEYPad_Pop(GPIO_TypeDef *GPIOx);

uint16_t GPIO_PortRead(GPIO_TypeDef *GPIOx);

uint16_t KEYPAD_Scan(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan1(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan2(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan3(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan4(GPIO_TypeDef *GPIOx);


#endif 

