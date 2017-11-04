#include "systick.h"


/************************************************************************************
**函数说明：
**系统时钟systick使能
**
************************************************************************************/

void Systick_initial(void)
{
//	if(SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC))
//	{
//		while(1);
//	}
//	
	RCC_ClocksTypeDef rcc_clocks;
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	 
	 
    RCC_GetClocksFreq(&rcc_clocks);
	 
    SysTick_Config(rcc_clocks.HCLK_Frequency / OS_TICKS_PER_SEC);

}



