#include "motor.h"
#include "tim.h"
#include "main.h"
#include "encoder.h"

extern __IO uint16_t PWM_Duty;
extern __IO int para;

/**
  * @brief  �����ĸ����PWM
  * @param  �ĸ����PWM
  * @retval ��
  */
void Set_Pwm(int pwm)
{
	 TIM_motor->CCR1=pwm;		//���PWMֵ
}


/**
  * @brief  ���������ʼ��
  * @param  ��
  * @retval ��
  */
void Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim_motor,TIM_CHANNEL_1);	
}


/**
  * @brief  ����ر�
  * @param  ��
  * @retval ��
  */
void Motor_Close(void)
{
	HAL_TIM_PWM_Stop(&htim_motor,TIM_CHANNEL_1);
}


/**
  * @brief  �������PWM�޷�
  * @param  ��
  * @retval ��
  */
void Motor_Limt(void)
{
	/* ����������ֵ������ǰ����ٶ� */
	if((para<-4)||(para>4)) // ���� PID ��������������СʱƵ�����������𵴡�
	{
		PWM_Duty +=para/10;  																																		//400
	}        
	if(PWM_Duty>9999)PWM_Duty=9999;  
	if(PWM_Duty<1)PWM_Duty=1;
}
