#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H

#include "stm32f10x.h"



/*********************************************/
/***TB6612FNG Pin  *** Hardware---mapped******/
//A端口
#define AIN1_GPIO_PORT    			GPIOC	             
#define AIN1_GPIO_CLK 	    		RCC_APB2Periph_GPIOC		
#define AIN1_GPIO_PIN				GPIO_Pin_8		       
#define AIN2_GPIO_PORT    			GPIOC		             
#define AIN2_GPIO_CLK 	    		RCC_APB2Periph_GPIOC		
#define AIN2_GPIO_PIN				GPIO_Pin_7
#define TB6612FNG_PWMA_GPIO_PORT    GPIOA		             
#define TB6612FNG_PWMA_GPIO_CLK	    RCC_APB2Periph_GPIOA		
#define TB6612FNG_PWMA_GPIO_PIN		GPIO_Pin_8

//B端口

#define BIN1_GPIO_PORT    				GPIOA		             
#define BIN1_GPIO_CLK 	    			RCC_APB2Periph_GPIOA		
#define BIN1_GPIO_PIN					GPIO_Pin_10		       
#define BIN2_GPIO_PORT    				GPIOA		             
#define BIN2_GPIO_CLK 	    			RCC_APB2Periph_GPIOA		
#define BIN2_GPIO_PIN					GPIO_Pin_11
#define TB6612FNG_PWMB_GPIO_PORT    	GPIOA		             
#define TB6612FNG_PWMB_GPIO_CLK	        RCC_APB2Periph_GPIOA		
#define TB6612FNG_PWMB_GPIO_PIN			GPIO_Pin_9

//使能PWM引脚

#define TB6612FNG_STBY_GPIO_PORT    	GPIOC		             
#define TB6612FNG_STBY_GPIO_CLK 	    RCC_APB2Periph_GPIOC		
#define TB6612FNG_STBY_GPIO_PIN			GPIO_Pin_9
 
/***END**************************************************/
/********************************************************/

/***TB6612FNG---function****/

#define TB6612FNG_PWM_ENABLE			GPIO_SetBits(TB6612FNG_STBY_GPIO_PORT, TB6612FNG_STBY_GPIO_PIN);
#define TB6612FNG_PWM_DISABLE			GPIO_ResetBits(TB6612FNG_STBY_GPIO_PORT, TB6612FNG_STBY_GPIO_PIN);

#define motorA_STOP_STATION				{GPIO_ResetBits(AIN1_GPIO_PORT, AIN1_GPIO_PIN);GPIO_ResetBits(AIN2_GPIO_PORT, AIN2_GPIO_PIN);}
#define motorA_FORWARD_STATION			{GPIO_SetBits(AIN1_GPIO_PORT, AIN1_GPIO_PIN);GPIO_ResetBits(AIN2_GPIO_PORT, AIN2_GPIO_PIN);}
#define motorA_BACK_STATION				{GPIO_SetBits(AIN2_GPIO_PORT, AIN2_GPIO_PIN);GPIO_ResetBits(AIN1_GPIO_PORT, AIN1_GPIO_PIN);}

#define motorB_STOP_STATION				{GPIO_ResetBits(BIN1_GPIO_PORT, BIN1_GPIO_PIN);GPIO_ResetBits(BIN2_GPIO_PORT, BIN2_GPIO_PIN);}
#define motorB_FORWARD_STATION			{GPIO_SetBits(BIN1_GPIO_PORT, BIN1_GPIO_PIN);GPIO_ResetBits(BIN2_GPIO_PORT, BIN2_GPIO_PIN);}
#define motorB_BACK_STATION				{GPIO_SetBits(BIN2_GPIO_PORT, BIN2_GPIO_PIN);GPIO_ResetBits(BIN1_GPIO_PORT, BIN1_GPIO_PIN);}

void Motor_Controller_Init(void);



#endif //(bsp_motor.h)

