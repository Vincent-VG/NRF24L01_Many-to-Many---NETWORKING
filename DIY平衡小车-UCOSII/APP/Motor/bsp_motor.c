#include "bsp_motor.h"
#include "bsp_tim_pwm.h"

static void TB6612FNG_GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	//RCC enable
	RCC_APB2PeriphClockCmd( AIN1_GPIO_CLK | 
							AIN2_GPIO_CLK | 
							BIN1_GPIO_CLK |
							BIN2_GPIO_CLK |
						
							
							TB6612FNG_STBY_GPIO_CLK, ENABLE); 
														 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	//方向引脚
	GPIO_InitStructure.GPIO_Pin = AIN1_GPIO_PIN;
	GPIO_Init(AIN1_GPIO_PORT, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = AIN2_GPIO_PIN;
	GPIO_Init(AIN2_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = BIN1_GPIO_PIN;
	GPIO_Init(BIN1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BIN2_GPIO_PIN;
	GPIO_Init(BIN2_GPIO_PORT, &GPIO_InitStructure);
	
	//PWM引脚
//	GPIO_InitStructure.GPIO_Pin = TB6612FNG_PWMA_GPIO_PIN;
//	GPIO_Init(TB6612FNG_PWMA_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin = TB6612FNG_PWMB_GPIO_PIN;
//	GPIO_Init(TB6612FNG_PWMB_GPIO_PORT, &GPIO_InitStructure);
	
	//使能脚
	GPIO_InitStructure.GPIO_Pin = TB6612FNG_STBY_GPIO_PIN;
	GPIO_Init(TB6612FNG_STBY_GPIO_PORT, &GPIO_InitStructure);
	
	
	motorA_FORWARD_STATION	
	motorB_FORWARD_STATION	
	TB6612FNG_PWM_ENABLE
	
}

void Motor_Controller_Init(void)
{
	TB6612FNG_GPIO_Config();
}





