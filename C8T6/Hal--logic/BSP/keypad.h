#ifndef __KEYPAD_H
#define __KEYPAD_H
#include "stm32f1xx_hal.h"

#define KEY_PASG_PORT  GPIOA
#define KEY_BIT_PORT  GPIOA


#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


void Key_Logic(void);									//����ɨ���ܳ���
void KEYPad_Pop(GPIO_TypeDef *GPIOx);			//�����˿ڶ�ȡ
uint16_t GPIO_PortRead(GPIO_TypeDef *GPIOx);	//GPIO�˿ڶ�ȡ
uint16_t KEYPAD_Scan(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan1(GPIO_TypeDef *GPIOx);
void KEY_Delay(__IO uint32_t i);

#endif 

