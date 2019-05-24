
/**
  ******************************************************************************
  * @file           : main.c
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


__IO uint16_t time_count=0;        // ʱ�������ÿ1ms����һ(��ζ�ʱ��Ƶ���й�)
__IO uint16_t time_count2=0;

__IO uint32_t CaptureNumber=0;     // �������������ز���
__IO uint8_t  start_encoder_flag=0;
__IO uint8_t  start_flag=0;
__IO int PWM_Duty;
__IO int count;
__IO int error0;
__IO int para1;
__IO int para2;

__IO int time_key_count=0;
__IO int key_open=0;       	//�ж�ʹ��һ�ΰ���
__IO int key_after_jixie=0; //ʧ�ܻ�е���㣬ʹ�ܰ������룻
__IO int i=0; 							//���ڰ������������λ����
__IO int keyvalue1=0;				//���ڿ�����������
__IO int keyvalue2=0;				//���ڴ�����������
__IO int key_last=0;				
__IO int key_in_flag=0;
__IO int key_out_flag=0;
__IO int key_finish=0;			//���һ�������
__IO int key_clear_flag=0;
__IO int open_flag=0;
__IO int close_flag=0;
int success_sub=0;
unsigned int success_count=0;
int success=0;
int success_clear=0;
int Weight = 0;        //ѹ��������ز���
int Weight_itr = 0; 
int key_str[5];

__IO int time_total=0;   //ϵͳ����ʱ


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

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
	
	HAL_TIM_Base_Start(&htim1);  //��ʼ����ʱ��
	HAL_TIM_Base_Start(&htim2);	
	HAL_TIM_Base_Start_IT(&htim3);

	Motor_Init();   //��ʼ�������������
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);		
	PID_Init(&Motor_PowerPID,PID_Motor_KP1,PID_Motor_KI1,PID_Motor_KD1);
	PID_Init(&Motor_SpeedPID,PID_Motor_KP2,PID_Motor_KI2,PID_Motor_KD2);
	
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
		printf("INIT__PASS����  \r\n");		//Ӳ����ʼ���ɹ�
	
	//////////��OLED��ʾװ�á�///////////
	
		OLED_ShowCHinese(6,0,7);//���������ϵͳ
		OLED_ShowCHinese(24,0,8);
		OLED_ShowCHinese(42,0,9);
		OLED_ShowCHinese(60,0,10);
		OLED_ShowCHinese(78,0,11);
		OLED_ShowCHinese(96,0,12);
		OLED_ShowCHinese(112,0,13);
		
		OLED_ShowCHinese(6,2,14);//Ŀ������ֵ��
		OLED_ShowCHinese(22,2,15);
		OLED_ShowCHinese(38,2,16);
		OLED_ShowCHinese(54,2,17);
		OLED_ShowCHinese(70,2,19);
		OLED_ShowString(120,2,"g",16);  	

		
		OLED_ShowCHinese(6,4,20);//��ǰ����ֵ��
		OLED_ShowCHinese(22,4,21);
		OLED_ShowCHinese(38,4,22);
		OLED_ShowCHinese(54,4,23);
		OLED_ShowCHinese(70,4,19);
		OLED_ShowString(120,4,"g",16);  	

		
		OLED_ShowCHinese(6,6,27);//ʱ�䣺
		OLED_ShowCHinese(22,6,28);
		OLED_ShowCHinese(38,6,19);
		OLED_ShowString(78,6,".",16);  
		OLED_ShowString(100,6,"s",16);  	
	
	/////////////////////////////////////
	
	
	//////////������װ�ó�ʼ������///////////////////
	while(1)
	{	
		if(key_open==1)
		{
			keyvalue2=KEYPAD_Scan(KEY_PASG_PORT);
			if(open_flag==1)break;
			
			if(keyvalue2==12&&key_after_jixie==0)//��ʱ����ת
				{
					Set_Pwm(9999);	
					HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_SET);
					key_open=0;         //���������־λ����Ϊ��Ҫ���밴���߼�������
				}
		
			if(keyvalue2==13&&key_after_jixie==0)		//˳ʱ����ת
			{
				Set_Pwm(6000);	
				HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);
				key_open=0;         //���������־λ����Ϊ��Ҫ���밴���߼�������
			}	
		
			if(keyvalue2==14&&key_after_jixie==0)		//ֹͣת��
			{	
				HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port,MOTOR_IN2_Pin,GPIO_PIN_RESET);
				key_open=0;         //���������־λ����Ϊ��Ҫ���밴���߼�������
			}			
			
			if(keyvalue2==15)
			{
				key_after_jixie=1;
			}
			
			if(key_after_jixie==1)
			{
				Key_Logic();					//��������ɨ��Ͱ�������;�����ȵ��������Ƶû�е��λ��������Ŀ��ֵ��
			}			
		}		
		 Weight = -Get_Weight();		
		 OLED_Show();
	}
	
			//////////����������de����////////////
		printf("														����													\r\n");
		start_flag=1;          					//�����δ�ʱ���Ķ�ʱ
//		start_encoder_flag=1;    				 //����PID�ĵ��ڱ�־	
		Get_Maopi();
		TIM2 -> CNT=0;
		success_count=0;
		time_total=0;
	
  while (1)
  {
			Weight = -Get_Weight();
			Key_Logic();					//��������ɨ��Ͱ�������;	
			OLED_Show();
			printf("\nĿ�꣺	%d  ѹ����%d	  ��ֵ%d	para1���� %d \r\n",Motor_PowerPID.SetPoint,Weight_itr,Motor_PowerPID.SetPoint-Weight_itr,para1);    				
			printf("\n										Ŀ�꣺%d  ������%d	��ֵ ��%d	 pid���㣺%d ռ�ձȣ�%d\n\r\n",para1,(int)count,(int)(para1-count),para2,PWM_Duty);   
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	
  }
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
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/100);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */



/**
  * ��������: ϵͳ�δ�ʱ���жϻص�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ÿ����һ�εδ�ʱ���жϽ���ûص�����һ��
  */
void HAL_SYSTICK_Callback(void)
{	

		/* �������в��� */
		Weight_itr=Weight;
//			printf("\n����ֵΪ:	��������������������		%d\r\n",Weight_itr);
	
//	if(TIM2->CNT==0)success_count++;
//	if(success_count>=20){time_total=0;success=1;}
//	else time_total++;				//����OLED��ʱ����ʾ
//			
	if(success==0)
	{
		time_total++;
		if((error0<=5)||(error0>=-5))
		{
			success_count++;
		}
		if(success_count>=20)
		{
			success=1;
			LED_ON;
		}
		else {success=0;LED_OFF;}	
	}
	
//	if(success==1)
//	{
//		if((error0>5)||(error0<-5))
//		{
//			success_count--;
//		}				
//		if(success_count<=17)
//		{
//			success=0;
//			time_total=0;			
//			LED_OFF;
//		}
//	}
	
	
		
					
	
  if(start_flag) 					// �ȴ�һ�г�ʼ����ɺ�ſ�ʼ��ʱ
  {
		time_count++;
				 
			if(time_count==6)
			{
							if(start_encoder_flag==1)
						{	
							/* ���⻷���ٶȲ���*/
							
							error0=Weight_itr-Motor_PowerPID.SetPoint;
							para1=Inc_PID_Calc2(&Motor_PowerPID,Weight_itr);      /* �����õ�λ��ʽPID��������ֵ */		
							if(para1<=0)para1=-para1;
							if(para1>375)para1=375;
							PID_SetPoint(&Motor_SpeedPID,para1);	
							
							
							/*���ڻ����������� */
							
							count=(short)TIM2->CNT;   		//��ñ�������ֵ��
							if(count<=0)count=-count;   	 //�ٶȻ�����Ҫ������
							para2=Inc_PID_Calc1(&Motor_SpeedPID,count);                  /* �����õ�����ʽPID��������ֵ */
							PWM_Duty +=para2;
								
							if(PWM_Duty<2000)PWM_Duty=2000;   	//�޷�
							if(PWM_Duty>10000)PWM_Duty=10000;		
							
							Motor_Dirc();     					//�б���
							Set_Pwm(PWM_Duty);				
							
			//				printf("\nĿ�꣺	%d  ѹ����%d	  ��ֵ%d	para1���� %d \r\n",Motor_PowerPID.SetPoint,Weight_itr,Weight_itr-Motor_PowerPID.SetPoint,para1);    				
			//				printf("\n										Ŀ�꣺%d  ������%d	��ֵ ��%d	 pid���㣺%d ռ�ձȣ�%d\n\r\n",para1,(int)count,(int)(para1-count),para2,PWM_Duty);   
						
						TIM2 -> CNT=0;
						}				
				time_count=0;
			}
			
	}
}




/**
  * ��������: ������ģʽ�¶�ʱ���Ļص�����
  * �������: htim����ʱ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	time_total++;						//����OLED��ʱ����ʾ
//	OLED_Show();
	 if (htim == (&htim3))
	{
		time_key_count++;
		if(time_key_count==100)
		{

			//////////���̱�־λ////////////////
//			printf("READDDDDDDDDDDDDD����  \r\n");
			if(keyvalue2==10)open_flag=1;
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
