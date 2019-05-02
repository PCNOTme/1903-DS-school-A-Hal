#ifndef __PID_H
#define __PID_H
#include "stm32f1xx_hal.h"

//ËÙ¶È»·
#define PID_Motor_KP1  1     //
#define PID_Motor_KI1 0  //0.7:2.884  0.6:2.472//3.8
#define PID_Motor_KD1 0

#define PID_Motor_KP2  1.2   // 
#define PID_Motor_KI2 0  //
#define PID_Motor_KD2 0

typedef volatile struct __PIDStruct
{
	int SetPoint;
	float Proportion;
	float Integral;
	float Derivative;
	float LastError;
	float PrevError;
	float LastErrorSum;
}PIDStruct;  
extern PIDStruct Motor_PowerPID;
extern PIDStruct Motor_SpeedPID;

void Pid_control(void);
void PID_SetPoint(PIDStruct * pidStuc, int SetPoint);
		
int Inc_PID_Calc1(PIDStruct * pidStuc,int NextPoint);
int Inc_PID_Calc2(PIDStruct * pidStuc,int NextPoint);


void Position_Motor_PID_Calc(PIDStruct * pidStuc,int SetPoint,float currentPoint,float acceptError, int limitValue);

void PID_Init(PIDStruct * pidStuc, float kp, float ki, float kd);

#endif
