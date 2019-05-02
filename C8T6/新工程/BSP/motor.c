#include "motor.h"
#include "tim.h"
#include "main.h"
#include "encoder.h"


extern  __IO float error0;
extern  int PWM_Duty;
extern  int para1;
extern  int para2;
extern  float Weight;
extern int key_str[5];

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
  * @brief  �������PWM����
  * @param  ��
  * @retval ��
  */
void Motor_Dirc(void)
{
	/* ���ݡ�������������ֵ������ǰ�������*/
	if(Weight>=key_str[4])   		//��ʱ����ת
	{
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_SET);
	}
		if(Weight<key_str[4]) 				//˳ʱ����ת
	{
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);	
	}  
	
	
//	/* ���ݡ���������������ֵ������ǰ�������*/
//		if(Weight>=speed_point)   		//��ʱ����ת
//	{
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_SET);
//	}  
//	
//		if(Weight<speed_point) 				//˳ʱ����ת
//	{
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);	
//	}  
	
}


/**
  * @brief  �������PWM�޷�
  * @param  ��
  * @retval ��
  */
void Motor_Limt(void)
{
//	/* ����������ֵ������ǰ����ٶ� */
	if((para1<-10)||(para1>10)) // ���� PID ��������������СʱƵ�����������𵴡�            //100����
	{
		PWM_Duty+=para1;  																																		//ʮ��Ƶ
	}
//	   PWM_Duty+=para1;  	
	
//	  if(error0<80&&error0>-80)
//		{  if(PWM_Duty>6000)PWM_Duty=6000 ;
//		}
//		if(error0<40&&error0>-40)
//		{  if(PWM_Duty>4500)PWM_Duty=4500 ;
//		}
//			if((10<error0&&error0<20)&&(-10>error0&&error0>-20))
//		{  if(PWM_Duty>4000)PWM_Duty=4000 ;
//		}

   if(PWM_Duty<-10000)PWM_Duty=-10000; 
	
}
