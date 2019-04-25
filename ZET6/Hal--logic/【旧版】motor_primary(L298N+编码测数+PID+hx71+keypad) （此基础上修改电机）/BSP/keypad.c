#include "keypad.h"
#include "main.h"

extern __IO int key_open;       	//中断使能一次按键
extern __IO int i; 							//用在按键输入的数组位数；
extern __IO int keyvalue1;				//用在开机按键输入
extern __IO int keyvalue2;				//用在待机按键输入
extern __IO int key_last;
extern __IO int key_in_flag;
extern __IO int key_out_flag;
extern __IO int key_clear_flag;
extern __IO int open_flag;
extern __IO int close_flag;

/**
  * @brief  读取整个GPIO的值
  * @param  定时器结构体
  * @retval 一个无符号8位的返回值
  */
void Key_Logic()
{
		////*开启扫描*////
		if(key_open==1)
		{
			keyvalue2=KEYPAD_Scan(KEY_PASG_PORT);
			key_open=0;
			printf("												wosaoninnnnnnnnnnnnnnnn			\r\n\r\n");		
		}	
		
//		////*开启输入*////
//		if(key_in_flag==1)
//		{
//			printf("													开始拟的输入					\r\n\r\n");		
//			HAL_Delay(2000);					
//			i++;
//			key_str[i]=keyvalue2;
//				if(key_out_flag==1)
//				{
//					key_str[4]=key_str[0]*1000+key_str[1]*100+key_str[2]*10+key_str[3];   //仅限输入4位数字，单位为g
//					key_str[4]=key_last/1000;	 //单位  Kg
//					i=0;
//					printf("设定了的目标值是 ………………………………………………………………    %d	kg\r\n\r\n",key_str[4]);

//					start_encoder_flag=0;			//可以显示当前的拉力值但是不可以做调整；
//					Motor_Close();   				//防止输入期间影响电机工作；		
//					key_out_flag=0;
//					key_in_flag=0;
//				}	
//		}
			
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
	u16 keyvalue = 0;
	keyvalue=KEYPAD_Scan1(KEY_PASG_PORT);
//	HAL_Delay(10);
	keyvalue=KEYPAD_Scan2(KEY_PASG_PORT);
//	HAL_Delay(10);
	keyvalue=KEYPAD_Scan3(KEY_PASG_PORT);
//	HAL_Delay(10);
	keyvalue=KEYPAD_Scan4(KEY_PASG_PORT);
//	HAL_Delay(10);
	return keyvalue;
}


uint16_t KEYPAD_Scan1(GPIO_TypeDef *GPIOx)
{
	u16 keyvalue = 0;
	u32 readvalue = 0;
	KEY_PASG_PORT->BRR |=0x01<<3;
	KEY_PASG_PORT->BSRR=0x01;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;

	if(readvalue != 0x0000)
	{
		HAL_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue = 1;break;
				case (0x0020):keyvalue = 2;break;
				case (0x0040):keyvalue = 3;break;
				case (0x0080):keyvalue = 12;break;
			}
			while(readvalue != 0x0000)
			{
				readvalue = GPIO_PortRead(KEY_BIT_PORT);
				readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue);	
			}
		}
	}
	return keyvalue;
}



uint16_t KEYPAD_Scan2(GPIO_TypeDef *GPIOx)
{
	u16 keyvalue = 0;
	u32 readvalue = 0;
	KEY_PASG_PORT->BRR |=0x01;
	KEY_PASG_PORT->BSRR |=0x01<<1;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;
	
	if(readvalue != 0x0000)
	{
		HAL_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue = 4;break;
				case (0x0020):keyvalue = 5;break;
				case (0x0040):keyvalue = 6;break;
				case (0x0080):keyvalue = 13;break;
			}
			while(readvalue != 0x0000)
			{
				readvalue = GPIO_PortRead(KEY_BIT_PORT);
				readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue);	
			}
		}
	}
	return keyvalue;

}



uint16_t KEYPAD_Scan3(GPIO_TypeDef *GPIOx)
{
  u16 keyvalue = 0;
	u32 readvalue = 0;
	
	KEY_PASG_PORT->BRR |=0x01<<1;
	KEY_PASG_PORT->BSRR |=0x01<<2;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;

	if(readvalue != 0x0000)
	{
		HAL_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue = 7;break;
				case (0x0020):keyvalue = 8;break;
				case (0x0040):keyvalue = 9;break;
				case (0x0080):keyvalue =14;break;
			}
			while(readvalue != 0x0000)
			{
					readvalue = GPIO_PortRead(KEY_BIT_PORT);
					readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue);	
			}

		}
	}
	return keyvalue;

}



uint16_t KEYPAD_Scan4(GPIO_TypeDef *GPIOx)
{
	 u16 keyvalue = 0;
	u32 readvalue = 0;
	
	KEY_PASG_PORT->BRR|=0x01<<2;
	KEY_PASG_PORT->BSRR|=0x01<<3;
	readvalue = GPIO_PortRead(KEY_BIT_PORT);
	readvalue &= 0x00f0;

	if(readvalue != 0x0000)
	{
		HAL_Delay(3);
		if(readvalue != 0x0000)
		{
			readvalue = GPIO_PortRead(KEY_BIT_PORT);
			readvalue &= 0x00f0;
			switch(readvalue)
			{
				case (0x0010):keyvalue = 10;break;
				case (0x0020):keyvalue = 0;break;
				case (0x0040):keyvalue = 11;break;
				case (0x0080):keyvalue = 15;break;
			}
			while(readvalue != 0x0000)
			{
					readvalue = GPIO_PortRead(KEY_BIT_PORT);
					readvalue &= 0x00f0;
				printf("										值为  %d  \r\n",keyvalue);	
			}
		}
	}
	return keyvalue;

}

