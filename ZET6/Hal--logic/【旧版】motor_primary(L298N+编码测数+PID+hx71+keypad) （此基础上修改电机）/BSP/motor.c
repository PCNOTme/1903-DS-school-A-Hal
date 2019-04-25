#include "motor.h"
#include "tim.h"
#include "main.h"
#include "encoder.h"

extern __IO uint16_t PWM_Duty;
extern __IO int para;

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
}


/**
  * @brief  电机关闭
  * @param  无
  * @retval 无
  */
void Motor_Close(void)
{
	HAL_TIM_PWM_Stop(&htim_motor,TIM_CHANNEL_1);
}


/**
  * @brief  电机驱动PWM限幅
  * @param  无
  * @retval 无
  */
void Motor_Limt(void)
{
	/* 根据增量数值调整当前电机速度 */
	if((para<-4)||(para>4)) // 不做 PID 调整，避免误差较小时频繁调节引起震荡。
	{
		PWM_Duty +=para/10;  																																		//400
	}        
	if(PWM_Duty>9999)PWM_Duty=9999;  
	if(PWM_Duty<1)PWM_Duty=1;
}
