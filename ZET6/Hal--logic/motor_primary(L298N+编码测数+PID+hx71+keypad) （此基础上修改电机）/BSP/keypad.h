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

/*�⻷����PID����*/
#define PID_Motor_KP1 1  
#define PID_Motor_KI1 0  
#define PID_Motor_KD1 0
/*�ڻ�����PID����*/
#define PID_Motor_KP2 20    
#define PID_Motor_KI2 4  
#define PID_Motor_KD2 0

void Key_Logic(void);									//����ɨ���ܳ���
void KEYPad_Pop(GPIO_TypeDef *GPIOx);			//�����˿ڶ�ȡ
uint16_t GPIO_PortRead(GPIO_TypeDef *GPIOx);	//GPIO�˿ڶ�ȡ

unsigned long HX711_Read(void);			//ѹ��������ɨ���ܳ���
long Get_Weight(void);					//���ë������			
void digitalWrite(GPIO_TypeDef * GPIO,int pin,int value);		//����д��	

void Motor_Init(void);			//�����ʼ��
void Set_Pwm(int pwm);			//д��pwmֵ
void Motor_Dirc(void);			//��������ж�
void Motor_Limt(void);			//���pwm�޷�
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

