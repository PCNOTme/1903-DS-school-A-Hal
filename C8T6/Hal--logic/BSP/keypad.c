#include "keypad.h"
#include "motor.h"
#include "pid.h"

extern __IO int key_open;       	//�ж�ʹ��һ�ΰ���
extern __IO int i; 							//���ڰ������������λ����
extern __IO int keyvalue1;				//���ڿ�����������
extern __IO int keyvalue2;				//���ڴ�����������
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
  * @brief  ��ȡ����GPIO��ֵ
  * @param  ��ʱ���ṹ��
  * @retval һ���޷���8λ�ķ���ֵ
  */
void Key_Logic()
{	
			////*��������*////
			if(key_in_flag==1)
			{
				Motor_Close();   				//��ֹ�����ڼ�Ӱ����������
				start_encoder_flag=0;			//������ʾ��ǰ������ֵ���ǲ�������������				
				printf("													��ʼ�������					\r\n\r\n");			
				
				if((keyvalue2>=0)&&(keyvalue2<=9)&&(keyvalue_flag==1))
				{
					keyvalue_flag=0;
					key_str[i]=keyvalue2;
					i++;
					printf("\n�ո�������һ��������          %d    i��ֵ��  %d    \r\n",keyvalue2,i);
				}
//				
//				if(key_clear_flag==1)
//				{
//					i--;
//				}	

				if((key_out_flag==1)&&(keyvalue_flag==1))
				{
						keyvalue_flag=0;			
						if(i==4)key_str[4]=key_str[0]*1000+key_str[1]*100+key_str[2]*10+key_str[3];   //��������4λ���֣���λΪg
						if(i==3)key_str[4]=key_str[0]*100+key_str[1]*10+key_str[2]; //��������3λ���֣���λΪg
						if(i==2)key_str[4]=key_str[0]*10+key_str[1]; 							  //��������2λ���֣���λΪg
						if(i==1)key_str[4]=key_str[0];  														 //��������1λ���֣���λΪg
//					key_str[4]=key_last/1000;	 //��λ  Kg
						i=0;
						PID_SetPoint(&Motor_PowerPID, key_str[4]);
						printf("�趨�˵�Ŀ��ֵ�� ����������������������������    %d	 \r\n\r\n",key_str[4]);		
//						HAL_Delay(10);
							
						key_finish=1;
						key_out_flag=0;
						key_in_flag=0;
					
					Motor_Init();   //��ʼ�������������  	
				start_encoder_flag=1;			//������ʾ��ǰ������ֵ������������									
				}	
			}
			
			////*����ɨ��*////
			if(key_open==1)
			{
				keyvalue2=KEYPAD_Scan(KEY_PASG_PORT);
				key_open=0;
			}	
			
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
	
	/*��һ�м���1/2/3/A */
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
				printf("										ֵΪ  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	/*�ڶ��м���4/5/6/B */
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
				printf("										ֵΪ  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	/*�����м���7/8/9/C */
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
				printf("										ֵΪ  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	/*�����м��̡��� */
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
				printf("										ֵΪ  %d  \r\n",keyvalue0);	
			}
			keyvalue_flag=1;
		}
	}
	
	return keyvalue0;
}


/**
  * @brief  ����ɨ����ʱ����
  * @param  i ��ʱʱ��
  * @retval ��
  */
void KEY_Delay(__IO uint32_t i)
{
	while(i--);
}


