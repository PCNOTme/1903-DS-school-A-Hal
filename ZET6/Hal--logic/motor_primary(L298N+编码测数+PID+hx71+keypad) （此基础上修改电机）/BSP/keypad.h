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

/*外环控制PID参数*/
#define PID_Motor_KP1 1  
#define PID_Motor_KI1 0  
#define PID_Motor_KD1 0
/*内环控制PID参数*/
#define PID_Motor_KP2 20    
#define PID_Motor_KI2 4  
#define PID_Motor_KD2 0

void Key_Logic(void);									//按键扫描总程序
void KEYPad_Pop(GPIO_TypeDef *GPIOx);			//按键端口读取
uint16_t GPIO_PortRead(GPIO_TypeDef *GPIOx);	//GPIO端口读取

unsigned long HX711_Read(void);			//压力传感器扫描总程序
long Get_Weight(void);					//获得毛重质量			
void digitalWrite(GPIO_TypeDef * GPIO,int pin,int value);		//数据写入	

void Motor_Init(void);			//电机初始化
void Set_Pwm(int pwm);			//写入pwm值
void Motor_Dirc(void);			//电机方向判断
void Motor_Limt(void);			//电机pwm限幅
void Motor_Close(void);			

uint16_t KEYPAD_Scan(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan1(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan2(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan3(GPIO_TypeDef *GPIOx);
uint16_t KEYPAD_Scan4(GPIO_TypeDef *GPIOx);


typedef volatile struct __PIDStruct
{
	float SetPoint;
	float Proportion;
	float Integral;
	float Derivative;
	float LastError;
	float PrevError;
}PIDStruct;  
extern PIDStruct Motor_PowerPID;
extern PIDStruct Motor_SpeedPID;

void PID_SetPoint(PIDStruct * pidStuc, int SetPoint);
		
int Inc_PID_Calc(PIDStruct * pidStuc,int NextPoint);

void Position_Motor_PID_Calc(PIDStruct * pidStuc,int SetPoint,float currentPoint,float acceptError, int limitValue);

void PID_Init(PIDStruct * pidStuc, float kp, float ki, float kd);

#endif 

