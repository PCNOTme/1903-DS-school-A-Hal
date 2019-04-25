#include "systick.h"
#include "stm32f4xx_hal.h"
#include "core_cm4.h"
void SysTick_Delay_Us( unsigned int us) 
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	for(i=0;i<us;i++)
	{
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}


void SysTick_Delay_Ms( unsigned int  ms)
{
	uint32_t i;	

	SysTick_Config(SystemCoreClock/1000);

	for(i=0;i<ms;i++)
	{
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

 
