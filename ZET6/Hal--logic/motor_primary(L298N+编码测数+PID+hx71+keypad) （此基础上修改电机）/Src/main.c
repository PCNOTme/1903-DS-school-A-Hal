
/**
  
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

#include "motor.h"
#include "pid.h"
#include "hx711.h"
#include "oled.h"
#include "keypad.h"

#include "stdio.h"
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

__IO uint16_t time_count=0;        // 时间计数，每1ms增加一(与滴定时器频率有关)
__IO uint16_t time_count2=0;
__IO uint16_t time_key_count=0;
__IO uint32_t CaptureNumber=0;     // 输入捕获数
__IO uint8_t  start_encoder_flag=0;
__IO uint8_t  start_flag=0;
__IO double encoder_speed=0;
int PWM_Duty;
__IO float count;
__IO float error0;
int para1;
int para2;

__IO int key_open=0;       	//中断使能一次按键
__IO int i=0; 							//用在按键输入的数组位数；
__IO int keyvalue1=0;				//用在开机按键输入
__IO int keyvalue2=0;				//用在待机按键输入
__IO int key_last=0;
__IO int key_in_flag=0;
__IO int key_out_flag=0;
__IO int key_clear_flag=0;
__IO int open_flag=0;
__IO int close_flag=0;

float Weight = 0;
int key_str[5];

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

	

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
//	OLED_Init();			//初始化OLED  
//	OLED_Clear(); 
	
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_Base_Start(&htim2);	
	HAL_TIM_Base_Start_IT(&htim3);

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	PID_Init(&Motor_PowerPID,PID_Motor_KP1,PID_Motor_KI1,PID_Motor_KD1);
	PID_Init(&Motor_SpeedPID,PID_Motor_KP2,PID_Motor_KI2,PID_Motor_KD2);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	Motor_Init();   
	PID_SetPoint(&Motor_PowerPID, power_point);
//	PID_SetPoint(&Motor_SpeedPID, speed_point);
	Get_Maopi();

	printf("INIT__PASS……  \r\n");	
	HAL_Delay(500);
 

	//////////开机程序///////////////////
	while(1)
	{
		if(key_open==1)
		{
			keyvalue1=KEYPAD_Scan(KEY_PASG_PORT);
			key_open=0;
			if(open_flag==1)break;
			
			if(keyvalue1==12)//逆时针旋转
				{Set_Pwm(9999);	
					HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_SET);}
			if(keyvalue1==13)		//顺时针旋转
			{Set_Pwm(6000);	
				HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);}		
			if(keyvalue1==14)		//停止转动
			{	HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);}
		}
	}
////		//////////拉力传感器部分/////////	
////		Weight = Get_Weight();
////		Weight = (float)Weight/1000.0f;
////		printf("拉力传感器回传值为:	%0.3f kg\r\n\r\n",Weight);	
////		printf("请开机并且输入目标拉力值！\r\n\r\n");
////		HAL_Delay(100);
	
	
	 ////////启动电机转动///////////
	
	printf("														开机													\r\n");
	HAL_Delay(500);
	
///////////////////////////////////////
	
//	start_flag=1;          			//开启滴答定时器的定时
	start_encoder_flag=1;     //开启PID的调节标志//
	
  while (1)
  {
		///包含按键扫描和按键输入////
		Key_Logic();
	
		printf("								当前keyvalue2  de  值  %d	\r\n",keyvalue2);
		HAL_Delay(50);
		
		////*关机识别*///
		if(close_flag==1)break;

		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */


  }
	
////////////关机程序///////////////////
	while(1)
	{
		HAL_TIM_Base_Stop_IT((&htim3));
		printf("SLLEEP……  \r\n");
		HAL_Delay(2000);
	}
//////////////////////////////////////
	
  /* USER CODE END 3 */


}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */


/**
  * 函数功能: 系统滴答定时器中断回调函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 每发生一次滴答定时器中断进入该回调函数一次
  */
void HAL_SYSTICK_Callback(void)
{
  if(start_flag) 					// 等待一切初始化完成后才开始计时
  {
      time_count++;         // 每1ms自动增一
    if(time_count==10)    																												
    {
				/* 拉力传感部分 */
			Weight = -Get_Weight();
//	Weight = (float)Weight/1000.0f;
		
			if(start_encoder_flag==1)
			{
//				/* 【外环】速度部分*/
				count=Weight; 			 /* 得到编码器计数值，数值越大说明速度越大 */
				error0=count-Motor_PowerPID.SetPoint;
				para1=Inc_PID_Calc2(&Motor_PowerPID,count);      /* 计数得到位置式PID的增量数值 */
//				printf("\n目标：%.2f 压力：%.2f	差值%.2f	pid计算%d 占空比->%d\r\n",Motor_PowerPID.SetPoint,Weight,count-Motor_PowerPID.SetPoint,para1,PWM_Duty); 
				printf("\n目标：	%.2f  压力：%.2f	  差值%.2f	para1计算 %d \r\n",Motor_PowerPID.SetPoint,Weight,count-Motor_PowerPID.SetPoint,para1);    				
//				Motor_Dirc();
//				Motor_Limt();
				if(para1<=0)para1=-para1;
				if(para1>200)para1=200;
			  PID_SetPoint(&Motor_SpeedPID,para1);	
				
				/*【内环】电流部分 */
				count=(short)TIM2->CNT; 
				if(count<=0)count=-count;
				para2=Inc_PID_Calc1(&Motor_SpeedPID,count);                  /* 计数得到增量式PID的增量数值 */
				PWM_Duty +=para2;
			  if(PWM_Duty<0)PWM_Duty=-PWM_Duty;		
				if(PWM_Duty<2000)PWM_Duty=2000;
		    if(PWM_Duty>10000)PWM_Duty=10000;		
        Motor_Dirc();
				Set_Pwm(PWM_Duty);					
				printf("																																				目标：%d  计数：%d	差值 ：%d	 pid计算：%d 占空比：%d\r\n\r\n",para1,(int)count,(int)(para1-count),para2,PWM_Duty);   
	
			}
			
			TIM2 -> CNT=0;
			time_count=0;
	
			
    }
//		if((time_count%10)==0){	printf("\n目标：	%.2f  压力：%.2f	  差值%.2f	para1计算 %d \r\n",Motor_PowerPID.SetPoint,Weight,count-Motor_PowerPID.SetPoint,para1);   }
  }
}



/**
  * 函数功能: 捕获定时器中断回调函数（编码器）
  * 输入参数: htim：定时器句柄
  * 返 回 值: 无
  * 说    明: 每发生一次滴答定时器中断进入该回调函数一次
  */
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim == &(htim2))
//	{
//		;
//	}
//}


/**
  * 函数功能: 非阻塞模式下定时器的回调函数
  * 输入参数: htim：定时器句柄
  * 返 回 值: 无
  * 说    明: 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	 if (htim == (&htim3))
	{
		time_key_count++;
		
		if(time_key_count==100)
		{
			//////////键盘标志位////////////////
//			printf("READDDDDDDDDDDDDD……  \r\n");
			if(keyvalue1==10)open_flag=1;
			if(keyvalue2==11)close_flag=1;
			if(keyvalue2==12)key_in_flag=1;
			if(keyvalue2==13)key_out_flag=1;
			if(keyvalue2==14)key_clear_flag=1;
			key_open=1;
			time_key_count=0;
		}	
	}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
