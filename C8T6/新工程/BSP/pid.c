#include "pid.h"
#include "hx711.h"
#include "motor.h"


extern __IO uint8_t  start_flag;
extern __IO uint16_t time_count;


extern __IO uint32_t CaptureNumber;     // �������������ز���
extern __IO uint8_t  start_encoder_flag;
extern __IO uint8_t  start_flag;
extern __IO int PWM_Duty;
extern __IO float count;
extern __IO float error0;
extern __IO int para1;
extern __IO int para2;

extern float Weight;        //ѹ��������ز���
extern int key_str[5];


//�ٶȱջ�PID�ṹ��
PIDStruct Motor_PowerPID;
PIDStruct Motor_SpeedPID;

///**
//  * @brief  PID���ں���
//  * @param  ��
//  * @param  ��
//  * @retval ��
//  */
///**************PID�������ں���********************************/
//void Pid_control()
//{
//	

//}	


/**
  * @brief  PID�ṹ���ʼ������
  * @param  pidStuc PID�ṹ��ָ��
  * @param  SetPoint Ŀ��ֵ
  * @retval ��
  */
/**************PID������ʼ��********************************/
void PID_Init(PIDStruct * pidStuc, float kp, float ki, float kd)
{
	pidStuc->Proportion = kp;
	pidStuc->Integral = ki;
	pidStuc->Derivative = kd;
	pidStuc->LastError = 0;
	pidStuc->PrevError = 0;
	pidStuc->LastErrorSum=0;
}

/********************����ʽPID�������************************************/
int Inc_PID_Calc1(PIDStruct * pidStuc,int NextPoint)
{
  int iError,iIncpid;                                 //��ǰ���
  iError=pidStuc->SetPoint-NextPoint;                    //��������
  iIncpid=(pidStuc->Proportion * iError)                 //E[k]��
              -(pidStuc->Integral * pidStuc->LastError)     //E[k-1]��
              +(pidStuc->Derivative * pidStuc->PrevError);  //E[k-2]��
              
  pidStuc->PrevError=pidStuc->LastError;                    //�洢�������´μ���
  pidStuc->LastError=iError;
  return(iIncpid);                                    //��������ֵ
}


int Inc_PID_Calc2(PIDStruct * pidStuc,int NextPoint)
{
  int iError,iIncpid;                                 //��ǰ���
  iError=pidStuc->SetPoint-NextPoint;
  pidStuc->LastErrorSum+=iError;
  iIncpid=(pidStuc->Proportion * iError)                 //E[k]��
              -(pidStuc->Integral * pidStuc->LastErrorSum)     //E[k-1]��
              +(pidStuc->Derivative * pidStuc->PrevError);  //E[k-2]��
              
  return(iIncpid);   
}

/**
  * @brief  PID�趨Ŀ��ֵ
  * @param  pidStuc PID�ṹ��ָ��
  * @param  setPoint Ŀ��ֵ
  * @retval ��
  */

void PID_SetPoint(PIDStruct * pidStuc, int SetPoint)
{
	pidStuc->SetPoint = SetPoint;
}
