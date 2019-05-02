#include "pid.h"
#include "hx711.h"
#include "motor.h"


extern __IO uint8_t  start_flag;
extern __IO uint16_t time_count;


extern __IO uint32_t CaptureNumber;     // 电机及编码器相关参数
extern __IO uint8_t  start_encoder_flag;
extern __IO uint8_t  start_flag;
extern __IO int PWM_Duty;
extern __IO float count;
extern __IO float error0;
extern __IO int para1;
extern __IO int para2;

extern float Weight;        //压力传感相关参数
extern int key_str[5];


//速度闭环PID结构体
PIDStruct Motor_PowerPID;
PIDStruct Motor_SpeedPID;

///**
//  * @brief  PID调节函数
//  * @param  无
//  * @param  无
//  * @retval 无
//  */
///**************PID参数调节函数********************************/
//void Pid_control()
//{
//	

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
