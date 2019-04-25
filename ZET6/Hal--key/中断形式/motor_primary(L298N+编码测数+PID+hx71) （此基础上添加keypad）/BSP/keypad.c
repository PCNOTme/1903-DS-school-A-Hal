#include "keypad.h"

 

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

