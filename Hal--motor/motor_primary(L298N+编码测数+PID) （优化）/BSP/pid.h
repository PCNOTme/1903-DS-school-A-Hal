#ifndef __PID_H
#define __PID_H
#include "stm32f1xx_hal.h"

//ËÙ¶È»·
#define PID_Motor_KP 3.6       //3~4
#define PID_Motor_KI 0  //0.7:2.884  0.6:2.472//3.8
#define PID_Motor_KD 0.1


typedef volatile struct __PIDStruct
{
	int SetPoint;
	float Proportion;
	float Integral;
	float Derivative;
	float LastError;
	float PrevError;
}PIDStruct;  
extern PIDStruct Motor_SpeedPID;

void PID_SetPoint(PIDStruct * pidStuc, int SetPoint);
		
int Inc_PID_Calc(PIDStruct * pidStuc,int NextPoint);

void Position_Motor_PID_Calc(PIDStruct * pidStuc,int SetPoint,float currentPoint,float acceptError, int limitValue);

void PID_Init(PIDStruct * pidStuc, float kp, float ki, float kd);

#endif
