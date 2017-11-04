#include "bsp_led.h"                  // Device header

void LED_Init(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启GPIOB和GPIOF的外设时钟*/
		RCC_APB2PeriphClockCmd( macLED1_GPIO_CLK | macLED2_GPIO_CLK, ENABLE); 

		

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		
		/*选择要控制的GPIOB引脚*/															   
		GPIO_InitStructure.GPIO_Pin = macLED1_GPIO_PIN;	
		/*调用库函数，初始化GPIOB0*/
		GPIO_Init(macLED1_GPIO_PORT, &GPIO_InitStructure);	
		
	
		GPIO_InitStructure.GPIO_Pin = macLED2_GPIO_PIN;	
		GPIO_Init(macLED2_GPIO_PORT, &GPIO_InitStructure);

//		/* 关闭所有led灯	*/
//		GPIO_SetBits(macLED1_GPIO_PORT, macLED1_GPIO_PIN);
		 
}
/*********************************************END OF FILE**********************/



