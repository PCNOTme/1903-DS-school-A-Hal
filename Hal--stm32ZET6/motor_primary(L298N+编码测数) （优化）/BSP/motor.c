#include "motor.h"
#include "tim.h"
#include "main.h"
#include "encoder.h"

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
  HAL_TIMEx_PWMN_Start(&htim_motor,TIM_CHANNEL_1);	
}

