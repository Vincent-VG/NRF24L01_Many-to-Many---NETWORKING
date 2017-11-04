#ifndef __BSP_TIM_H
#define __BSP_TIM_H

#include "stm32f10x.h"
#include <stm32f10x_tim.h>
/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里默认使用TIM4

#define            HIGH_TIM                   TIM1
#define            HIGH_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            HIGH_TIM_CLK               RCC_APB2Periph_TIM1
#define            HIGH_TIM_Period            7200-1
#define            HIGH_TIM_Prescaler         72-1

// TIM4 输出比较通道1
#define            HIGH_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            HIGH_TIM_CH1_PORT          GPIOA
#define            HIGH_TIM_CH1_PIN           GPIO_Pin_8

// TIM4 输出比较通道2
#define            HIGH_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            HIGH_TIM_CH2_PORT          GPIOA
#define            HIGH_TIM_CH2_PIN           GPIO_Pin_9

/***Function***Declare******************/
void TIM_PWM_Init(void);
void motorA_PWM_CTR(uint16_t cnt);
void motorB_PWM_CTR(uint16_t cnt);
#endif //(bsp_tim.h)
