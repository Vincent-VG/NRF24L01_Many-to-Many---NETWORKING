#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "stm32f10x.h"
#include <stm32f10x_exti.h>


#define KEY_IRQ_Handler			EXTI15_10_IRQHandler

/* 定义KEY连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的KEY引脚 */
#define macKEY1_GPIO_PORT    		GPIOC			           	/* GPIO端口 */
#define macKEY1_GPIO_CLK 	    	RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define macKEY1_GPIO_PIN			GPIO_Pin_14			        /* 连接到SCL时钟线的GPIO */
#define macKEY1_EXTI_PORTSOURCE		GPIO_PortSourceGPIOC			       
#define macKEY1_EXTI_PINSOURCE		GPIO_PinSource14			       
#define macKEY1_EXTI_LINE			EXTI_Line14	

#define macKEY2_GPIO_PORT    		GPIOC			            /* GPIO端口 */
#define macKEY2_GPIO_CLK 	    	RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define macKEY2_GPIO_PIN			GPIO_Pin_15			        /* 连接到SCL时钟线的GPIO */
#define macKEY2_EXTI_PORTSOURCE		GPIO_PortSourceGPIOC			       
#define macKEY2_EXTI_PINSOURCE		GPIO_PinSource15
#define macKEY2_EXTI_LINE			EXTI_Line15
/***STATION***MACRO******************************************************************/
#define KEY_ON		(int)1
#define KEY_OFF		(int)0


void KEY_Init(void);
//int Key1Scan ();
//int Key2Scan ();
#endif	//(bsp_key.h)
