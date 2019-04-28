#include "pid.h"

//�ٶȱջ�PID�ṹ��
PIDStruct Motor_PowerPID;
PIDStruct Motor_SpeedPID;

/**
  * @brief  ����ʽPID���㺯��
  * @param  pidStuc pid�ṹ��ָ��
  * @param  currentPoint �������ɼ�ֵ
  * @param  limieValue ����޷�
  * @param  acceptError ���
  * @retval ��
  */
//void Inc_PID_Calc(PIDStruct * pidStuc,int SetPoint,float currentPoint,float acceptError, int limitValue)
//{
//	float nowError,outPut;
//	pidStuc->SetPoint = SetPoint;
//	nowError = pidStuc->SetPoint - currentPoint;	
//	
//	//����޷�
////	if(pidStuc->PWMSum >= limitValue)
////	{
////		pidStuc->PWMSum = limitValue;
////	}else if (pidStuc->PWMSum <=   (-limitValue))
////	{
////		pidStuc->PWMSum = -limitValue;
////	}
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
