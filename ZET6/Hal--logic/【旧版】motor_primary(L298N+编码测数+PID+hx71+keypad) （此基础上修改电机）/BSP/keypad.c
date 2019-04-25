#include "keypad.h"
#include "main.h"

extern __IO int key_open;       	//�ж�ʹ��һ�ΰ���
extern __IO int i; 							//���ڰ������������λ����
extern __IO int keyvalue1;				//���ڿ�����������
extern __IO int keyvalue2;				//���ڴ�����������
extern __IO int key_last;
extern __IO int key_in_flag;
extern __IO int key_out_flag;
extern __IO int key_clear_flag;
extern __IO int open_flag;
extern __IO int close_flag;

/**
  * @brief  ��ȡ����GPIO��ֵ
  * @param  ��ʱ���ṹ��
  * @retval һ���޷���8λ�ķ���ֵ
  */
void Key_Logic()
{
		////*����ɨ��*////
		if(key_open==1)
		{
			keyvalue2=KEYPAD_Scan(KEY_PASG_PORT);
			key_open=0;
			printf("												wosaoninnnnnnnnnnnnnnnn			\r\n\r\n");		
		}	
		
//		////*��������*////
//		if(key_in_flag==1)
//		{
//			printf("													��ʼ�������					\r\n\r\n");		
//			HAL_Delay(2000);					
//			i++;
//			key_str[i]=keyvalue2;
//				if(key_out_flag==1)
//				{
//					key_str[4]=key_str[0]*1000+key_str[1]*100+key_str[2]*10+key_str[3];   //��������4λ���֣���λΪg
//					key_str[4]=key_last/1000;	 //��λ  Kg
//					i=0;
//					printf("�趨�˵�Ŀ��ֵ�� ������������������������������������������������    %d	kg\r\n\r\n",key_str[4]);

//					start_encoder_flag=0;			//������ʾ��ǰ������ֵ���ǲ�������������
//					Motor_Close();   				//��ֹ�����ڼ�Ӱ����������		
//					key_out_flag=0;
//					key_in_flag=0;
//				}	
//		}
			
}


/**
  * @brief  ��ȡ����GPIO��ֵ
  * @param  ��ʱ���ṹ��
  * @retval һ���޷���8λ�ķ���ֵ
  */
uint16_t GPIO_PortRead(GPIO_TypeDef *GPIOx)
{
	uint16_t portvalue = 0;
	portvalue=GPIOx->IDR;
	
	printf("\n                IO�ڶ�ֵΪ��  %d \r\n",portvalue);  
	return portvalue;

}


/**
  * @brief  ɨ����󰴼�
  * @param  ��
  * @retval ����һ������ֵ
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
				printf("										ֵΪ  %d  \r\n",keyvalue);	
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
				printf("										ֵΪ  %d  \r\n",keyvalue);	
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
				printf("										ֵΪ  %d  \r\n",keyvalue);	
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
				printf("										ֵΪ  %d  \r\n",keyvalue);	
			}
		}
	}
	return keyvalue;

}

