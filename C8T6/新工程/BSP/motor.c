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
  * @brief  电机驱动PWM方向
  * @param  无
  * @retval 无
  */
void Motor_Dirc(void)
{
	/* 根据【拉力】增量数值调整当前电机方向*/
	if(Weight>=key_str[4])   		//逆时针旋转
	{
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_SET);
	}
		if(Weight<key_str[4]) 				//顺时针旋转
	{
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);	
	}  
	
	
//	/* 根据【编码器】增量数值调整当前电机方向*/
//		if(Weight>=speed_point)   		//逆时针旋转
//	{
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_SET);
//	}  
//	
//		if(Weight<speed_point) 				//顺时针旋转
//	{
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);	
//	}  
	
}


/**
  * @brief  电机驱动PWM限幅
  * @param  无
  * @retval 无
  */
void Motor_Limt(void)
{
//	/* 根据增量数值调整当前电机速度 */
	if((para1<-10)||(para1>10)) // 不做 PID 调整，避免误差较小时频繁调节引起震荡。            //100以内
	{
		PWM_Duty+=para1;  																																		//十分频
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
