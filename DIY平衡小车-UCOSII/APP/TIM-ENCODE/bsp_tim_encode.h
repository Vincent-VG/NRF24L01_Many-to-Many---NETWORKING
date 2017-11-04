#ifndef __BSP_TIM_ENCODE_H
#define __BSP_TIM_ENCODE_H

#include "stm32f10x.h"
#include <stm32f10x_tim.h>

/***Parameter***/
#define TIM_Period_parameter   6000



/*****Hardeware mapped**********/
//Number_1
#define ENCODE1_TIM				TIM2
#define ENCODE1_TIM_CLK			RCC_APB1Periph_TIM2


#define TIM2_CH1_GPIO_PORT    	GPIOA			              
#define TIM2_CH1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		
#define TIM2_CH1_GPIO_PIN		GPIO_Pin_0			       
#define TIM2_CH2_GPIO_PORT    	GPIOA			              
#define TIM2_CH2_GPIO_CLK 	    RCC_APB2Periph_GPIOA		
#define TIM2_CH2_GPIO_PIN		GPIO_Pin_1	
//Number 2
#define ENCODE2_TIM				TIM4
#define ENCODE2_TIM_CLK			RCC_APB1Periph_TIM4


#define TIM4_CH1_GPIO_PORT    	GPIOB			              
#define TIM4_CH1_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define TIM4_CH1_GPIO_PIN		GPIO_Pin_6			       
#define TIM4_CH2_GPIO_PORT    	GPIOB			              
#define TIM4_CH2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define TIM4_CH2_GPIO_PIN		GPIO_Pin_7	


/******Functions---declare******/
void TIM_Encode_Init(void);
void Speed_Calculate (void);
#endif //(bsp_tim_encode.h)

