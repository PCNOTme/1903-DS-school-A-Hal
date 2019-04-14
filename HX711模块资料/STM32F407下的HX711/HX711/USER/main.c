#include "sys.h"
#include "usart.h"
#include "key.h"
#include "HX711.h"
#include "delay.h"

float Weight = 0;

int main(void)
{ 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	Init_Hx711();
	delay_ms(2000);
	Get_Maopi();
	delay_ms(100);
	
	while(1)
	{
	Weight = Get_Weight();
	Weight = (float)Weight/1000.0f;
	printf("%0.3f kg\n",Weight);	//串口显示重量
	delay_ms(1000);
	}
}

