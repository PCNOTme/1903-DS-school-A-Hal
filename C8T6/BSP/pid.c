#include "pid.h"

//速度闭环PID结构体
PIDStruct Motor_PowerPID;
PIDStruct Motor_SpeedPID;

/**
  * @brief  增量式PID计算函数
  * @param  pidStuc pid结构体指针
  * @param  currentPoint 传感器采集值
  * @param  limieValue 输出限幅
  * @param  acceptError 误差
  * @retval 无
  */
//void Inc_PID_Calc(PIDStruct * pidStuc,int SetPoint,float currentPoint,float acceptError, int limitValue)
//{
//	float nowError,outPut;
//	pidStuc->SetPoint = SetPoint;
//	nowError = pidStuc->SetPoint - currentPoint;	
//	
//	//输出限幅
////	if(pidStuc->PWMSum >= limitValue)
////	{
////		pidStuc->PWMSum = limitValue;
////	}else if (pidStuc->PWMSum <=   (-limitValue))
////	{
////		pidStuc->PWMSum = -limitValue;
////	}
//}


/**
  * @brief  PID结构体初始化函数
  * @param  pidStuc PID结构体指针
  * @param  SetPoint 目标值
  * @retval 无
  */
/**************PID参数初始化********************************/
void PID_Init(PIDStruct * pidStuc, float kp, float ki, float kd)
{
	pidStuc->Proportion = kp;
	pidStuc->Integral = ki;
	pidStuc->Derivative = kd;
	pidStuc->LastError = 0;
	pidStuc->PrevError = 0;
	pidStuc->LastErrorSum=0;
}

/********************增量式PID控制设计************************************/
int Inc_PID_Calc1(PIDStruct * pidStuc,int NextPoint)
{
  int iError,iIncpid;                                 //当前误差
  iError=pidStuc->SetPoint-NextPoint;                    //增量计算
  iIncpid=(pidStuc->Proportion * iError)                 //E[k]项
              -(pidStuc->Integral * pidStuc->LastError)     //E[k-1]项
              +(pidStuc->Derivative * pidStuc->PrevError);  //E[k-2]项
              
  pidStuc->PrevError=pidStuc->LastError;                    //存储误差，用于下次计算
  pidStuc->LastError=iError;
  return(iIncpid);                                    //返回增量值
}


int Inc_PID_Calc2(PIDStruct * pidStuc,int NextPoint)
{
  int iError,iIncpid;                                 //当前误差
  iError=pidStuc->SetPoint-NextPoint;
  pidStuc->LastErrorSum+=iError;
  iIncpid=(pidStuc->Proportion * iError)                 //E[k]项
              -(pidStuc->Integral * pidStuc->LastErrorSum)     //E[k-1]项
              +(pidStuc->Derivative * pidStuc->PrevError);  //E[k-2]项
              

  return(iIncpid);   
}

/**
  * @brief  PID设定目标值
  * @param  pidStuc PID结构体指针
  * @param  setPoint 目标值
  * @retval 无
  */

void PID_SetPoint(PIDStruct * pidStuc, int SetPoint)
{
	pidStuc->SetPoint = SetPoint;
}
