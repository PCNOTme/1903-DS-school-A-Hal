#include "keypad.h"
#include "motor.h"
#include "pid.h"

extern __IO int key_open;       	//中断使能一次按键
extern __IO int i; 							//用在按键输入的数组位数；
extern __IO int keyvalue1;				//用在开机按键输入
extern __IO int keyvalue2;				//用在待机按键输入
extern __IO int key_last;
extern __IO int key_in_flag;
extern __IO int key_out_flag;
extern __IO int key_finish;
extern __IO int key_clear_flag;
extern __IO int open_flag;
extern __IO int close_flag;

extern __IO uint8_t  start_encoder_flag;


extern int key_str[5];
u16 keyvalue_temp = 0;
u16 keyvalue_flag = 0;
u16 keyvalue0 = 0;


/**
  * @brief  读取整个GPIO的值
  * @param  定时器结构体
  * @retval 一个无符号8位的返回值
  */
void Key_Logic()
{	
			////*开启输入*////
			if(key_in_flag==1)
			{
				Motor_Close();   				//防止输入期间影响电机工作；
				start_encoder_flag=0;			//可以显示当前的拉力值但是不可以做调整；				
				printf("													开始拟的输入					\r\n\r\n");			
				
				if((keyvalue2>=0)&&(keyvalue2<=9)&&(keyvalue_flag==1))
				{
					keyvalue_flag=0;
					key_str[i]=keyvalue2;
					i++;
					printf("\n刚刚输入了一个按键：          %d    i的值是  %d    \r\n",keyvalue2,i);
				}
//				
//				if(key_clear_flag==1)
//				{
//					i--;
//				}	

				if((key_out_flag==1)&&(keyvalue_flag==1))
				{
						keyvalue_flag=0;			
						if(i==4)key_str[4]=key_str[0]*1000+key_str[1]*100+key_str[2]*10+key_str[3];   //仅限输入4位数字，单位为g
						if(i==3)key_str[4]=key_str[0]*100+key_str[1]*10+key_str[2]; //仅限输入3位数字，单位为g
						if(i==2)key_str[4]=key_str[0]*10+key_str[1]; 							  //仅限输入2位数字，单位为g
						if(i==1)key_str[4]=key_str[0];  														 //仅限输入1位数字，单位为g
//					key_str[4]=key_last/1000;	 //单位  Kg
						i=0;
						PID_SetPoint(&Motor_PowerPID, key_str[4]);
						printf("设定了的目标值是 ……………………………………    %d	 \r\n\r\n",key_str[4]);		
//						HAL_Delay(10);
							
						key_finish=1;
						key_out_flag=0;
						key_in_flag=0;
					
					Motor_Init();   //初始化电机、编码器  	
				start_encoder_flag=1;			//可以显示当前的拉力值并且做调整；									
				}	
			}
			
			////*开启扫描*////
			if(key_open==1)
			{
				keyvalue2=KEYPAD_Scan(KEY_PASG_PORT);
				key_open=0;
			}	
			
}


/**
  * @brief  读取整个GPIO的值
  * @param  定时器结构体
  * @retval 一个无符号8位的返回值
  */
uint16_t GPIO_PortRead(GPIO_TypeDef *GPIOx)
{
	uint16_t portvalue = 0;
	portvalue=GPIOx->IDR;
	
	printf("\n                IO口读值为：  %d \r\n",portvalue);  
	return portvalue;

}


/**
  * @brief  扫描矩阵按键
  * @param  无
  * @retval 返回一个按键值
  */

uint16_t KEYPAD_Scan(GPIO_TypeDef *GPIOx)
{
	keyvalue_temp=KEYPAD_Scan1(KEY_PASG_PORT);
//	HAL_Delay(10);
//	keyvalue_temp=KEYPAD_Scan2(KEY_PASG_PORT);
////	HAL_Delay(10);
//	keyvalue_temp=KEYPAD_Scan3(KEY_PASG_PORT);
////	HAL_Delay(10);
//	keyvalue_temp=KEYPAD_Scan4(KEY_PASG_PORT);
//	HAL_Delay(10);
	return keyvalue_temp;
}


uint16_t KEYPAD_Scan1(GPIO_TypeDef *GPIOx)
{
	
	/*第一行键盘1/2/3/A */
	static u32 readvalue;
	KEY_PASG_PORT->BRR |=0x01<<3;
	KEY_PASG_PORT->BSRR=0x01;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;

	if(readvalue != 0x0000)
	{
		KEY_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue0 = 1;break;
				case (0x0020):keyvalue0 = 2;break;
				case (0x0040):keyvalue0 = 3;break;
				case (0x0080):keyvalue0 = 12;break;
			}
			while(readvalue != 0x0000)
			{
				readvalue = GPIO_PortRead(KEY_BIT_PORT);
				readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	/*第二行键盘4/5/6/B */
	KEY_PASG_PORT->BRR |=0x01;
	KEY_PASG_PORT->BSRR |=0x01<<1;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;
	
	if(readvalue != 0x0000)
	{
		KEY_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue0 = 4;break;
				case (0x0020):keyvalue0 = 5;break;
				case (0x0040):keyvalue0 = 6;break;
				case (0x0080):keyvalue0 = 13;break;
			}
			while(readvalue != 0x0000)
			{
				readvalue = GPIO_PortRead(KEY_BIT_PORT);
				readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	/*第三行键盘7/8/9/C */
	KEY_PASG_PORT->BRR |=0x01<<1;
	KEY_PASG_PORT->BSRR |=0x01<<2;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;

	if(readvalue != 0x0000)
	{
		KEY_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue0 = 7;break;
				case (0x0020):keyvalue0 = 8;break;
				case (0x0040):keyvalue0 = 9;break;
				case (0x0080):keyvalue0 =14;break;
			}
			while(readvalue != 0x0000)
			{
					readvalue = GPIO_PortRead(KEY_BIT_PORT);
					readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	/*第四行键盘…… */
	KEY_PASG_PORT->BRR|=0x01<<2;
	KEY_PASG_PORT->BSRR|=0x01<<3;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;

	if(readvalue != 0x0000)
	{
		KEY_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue0 = 10;break;
				case (0x0020):keyvalue0 = 0;break;
				case (0x0040):keyvalue0 = 11;break;
				case (0x0080):keyvalue0 = 15;break;
			}
			while(readvalue != 0x0000)
			{
					readvalue = GPIO_PortRead(KEY_BIT_PORT);
					readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	return keyvalue0;
}


/**
  * @brief  按键扫描延时函数
  * @param  i 延时时间
  * @retval 无
  */
void KEY_Delay(__IO uint32_t i)
{
	while(i--);
}


