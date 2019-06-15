#include "hx711.h"
#include "gpio.h"

long HX711_Buffer = 0;
long Weight_Maopi = 0,Weight_Shiwu = 0;

#define GapValue 430
#define HIGH 1
#define LOW  0
#define HX711_PORT  GPIOB
#define HX711_I2C_SCK GPIO_PIN_8
#define HX711_I2C_DAT GPIO_PIN_9


//****************************************************
//获得延时
//****************************************************
void delay_us(uint8_t value)
{
	uint8_t i;
	for (i=value;i>0;i--);
}



//****************************************************
//写入高低电平
//****************************************************
void digitalWrite(GPIO_TypeDef * GPIO,int pin,int value)
{
	if(value==HIGH)//set 1
	{
		HAL_GPIO_WritePin(GPIO,pin,GPIO_PIN_SET);
	}
	if(value==LOW)//reset 0
	{
		HAL_GPIO_WritePin(GPIO,pin,GPIO_PIN_RESET);
	}
}

int digitalRead(GPIO_TypeDef * GPIO,int pin)
{
	return HAL_GPIO_ReadPin(GPIO,pin);
}



//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi()
{
	Weight_Maopi = HX711_Read();		
} 

//****************************************************
//称重
//****************************************************
long Get_Weight()
{
	HX711_Buffer = HX711_Read();
	Weight_Shiwu = HX711_Buffer;
	Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。
	Weight_Shiwu = (long)((float)Weight_Shiwu/GapValue); 	
	return Weight_Shiwu;
}

//****************************************************
//读取HX711芯片的值
//****************************************************
unsigned long HX711_Read(void)	//增益128
{
	unsigned long val = 0; 
	unsigned char i = 0; 
	
	//判断模块是否准备好
	while(HAL_GPIO_ReadPin(HX711_PORT,HX711_I2C_DAT));

	delay_us(1);   
	//sck 拉低
	HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_RESET);
	//再次判断是否准备好
	while(HAL_GPIO_ReadPin(HX711_PORT,HX711_I2C_DAT));
	
	for(i=0;i<24;i++) 
	{ 
		delay_us(100); 
		HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_SET);	   
		val=val<<1; 
		delay_us(1);  
		HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_RESET);	   
		if(HAL_GPIO_ReadPin(HX711_PORT,HX711_I2C_DAT))  
		val++; 
		delay_us(1); 
	} 

//	printf("WORK_ING  \r\n");
	HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_SET); 
	val = val^0x800000; 
	delay_us(1); 
	HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_RESET); 
	delay_us(1);  
	return val; 
}



////****************************************************

////读取HX711,对第一个交互力传感器

////****************************************************

//unsigned long HX711_Read(void)	//增益128

//{

//	unsigned long count; 

//	unsigned char i; 	

//	

//  	HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_RESET);//模块没准备好时，单片机在CLK线上输出低电平

//  	count=0;

//	int ii=0;

//    while(1)

//	{

//	    if(HAL_GPIO_ReadPin(HX711_PORT,HX711_I2C_DAT)==0)

//		{

//			delay_us(1);

//			if(HAL_GPIO_ReadPin(HX711_PORT,HX711_I2C_DAT)==0)

//			{

//				break;

//			}			

//		}

//			

//		ii++;

//		if(ii>=1000000)

//		{

//			break;

//		}

//	}

//	delay_us(1);

//  	for(i=0;i<24;i++)

//	{ 			

//		HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_SET);

//		delay_us(1);

//	  	count=count<<1; 	

//		HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_RESET);		

//	  	if(HAL_GPIO_ReadPin(HX711_PORT,HX711_I2C_DAT)==1)//读入数据

//		{

//			count++; 

//		}		

//			

//	} 

//	HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_SET);

//	delay_us(2);

//    count=count^0x800000;//第25个脉冲下降沿来时，转换数据

//	HAL_GPIO_WritePin(HX711_PORT,HX711_I2C_SCK,GPIO_PIN_RESET);

//	return(count);

//}

