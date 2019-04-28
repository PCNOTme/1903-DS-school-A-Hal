#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f1xx_hal.h"

void Motor_Init(void);
void Set_Pwm(int pwm);
void Motor_Dirc(void);
void Motor_Limt(void);
void Motor_Close(void);
	

#endif 
