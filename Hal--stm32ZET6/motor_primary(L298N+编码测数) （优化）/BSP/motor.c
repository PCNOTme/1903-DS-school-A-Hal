#include "motor.h"
#include "tim.h"
#include "main.h"
#include "encoder.h"

/**
  * @brief  设置四个电机PWM
  * @param  四个电机PWM
  * @retval 无
  */
void Set_Pwm(int pwm)
{
	 TIM_motor->CCR1=pwm;		//电机PWM值
}


/**
  * @brief  电机驱动初始化
  * @param  无
  * @retval 无
  */
void Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim_motor,TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim_motor,TIM_CHANNEL_1);	
}

