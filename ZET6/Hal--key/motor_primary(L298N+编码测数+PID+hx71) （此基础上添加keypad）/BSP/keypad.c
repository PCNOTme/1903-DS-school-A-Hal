#include "keypad.h"

#define KEY_PORT  GPIOB



void KEYPad_Init1(void)

{

	GPIO_InitTypeDef GPIO_InitStructure;

	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);//????,??GPIOB??

	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//???? B0-B3

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOF, &GPIO_InitStructure);

	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//???? B4-B7

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOF, &GPIO_InitStructure);

}


void KEYPad_Init2(void)

{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);//????,??GPIOB??

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//???? B0-B3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//???? B4-B7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
}
 


/**
  * @brief  读取整个GPIO的值
  * @param  定时器结构体
  * @retval 一个无符号8位的返回值
  */
uint8_t GPIO_PortRead(GPIO_TypeDef *GPIOx)
{
	static u8 portvalue = 0;
	GPIOx->ODR =portvalue;
	
	return portvalue;

}


/**
  * @brief  扫描矩阵按键
  * @param  无
  * @retval 返回一个按键值
  */

uint16_t KEYPAD_Scan()
{
		static u16 keyvalue = 0;
		u32 readvalue = 0;
		KEYPad_Init1();
		readvalue = GPIO_PortRead(KEY_PORT)；
		readvalue &= 0x00ff;

		if(readvalue != 0x000f)
		{
			delay_ms(8);
			if(readvalue != 0x000f)
			{
				readvalue = GPIO_ReadInputData(GPIOF);
				readvalue &= 0x00ff;
				switch(readvalue)
				{
					case (0x001f):keyvalue = 0;break;
					case (0x002f):keyvalue = 1;break;
					case (0x004f):keyvalue = 2;break;
					case (0x008f):keyvalue = 3;break;

				}
				KEYPad_Init2();
				delay_ms(5);
				readvalue = GPIO_ReadInputData(GPIOF);
				readvalue |= 0x00f0;
				readvalue &= 0x00ff;
				switch(readvalue)
				{
					case (0x00f1):keyvalue += 0;break;
					case (0x00f2):keyvalue += 4;break;
					case (0x00f4):keyvalue += 8;break;
					case (0x00f8):keyvalue += 12;break;
				}

				while(readvalue != 0x00f0)//??????
				{
					readvalue = GPIO_ReadInputData(GPIOF);//??????
					readvalue |= 0x00f0;
					readvalue &= 0x00ff;
				}
			}

		}

	return keyvalue;

}

