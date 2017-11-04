#include "led.h"


/************************************************************************************
**函数说明：
**1、开发板的LED0对应CPU的IO脚PB5；
**2、开发板的LED1对应CPU的IO脚PE5；
**3、IO脚为低电平时，LED亮；
**4、IO脚为高电平时，LED灭；
**5、使能外设PB与PE的时钟，设置IO脚为推挽输出，速率50MHz；
**
************************************************************************************/

void led_initial(void)
{
	GPIO_InitTypeDef	GPIO_Init_Struct;//定义GPIO初始化结构体
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//使能外设时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	//使能外设时钟
	
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_5;					//IO引脚为pin5
	
	GPIO_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;			//速率为50MHz
	
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_Out_PP;			//推挽输出
	
	GPIO_Init(GPIOB,&GPIO_Init_Struct);						//初始化PB
	
	GPIO_Init(GPIOE,&GPIO_Init_Struct);						//初始化PE
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);							//初始化设置引脚输出高电平，即LED为灭状态
	
	GPIO_SetBits(GPIOE,GPIO_Pin_5);							//初始化设置引脚输出高电平，即LED为灭状态
	

	
}



