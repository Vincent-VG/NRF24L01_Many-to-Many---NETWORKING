#include "bsp_tim_pwm.h"


static void TIM_PWM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//RCC-enable
	RCC_APB2PeriphClockCmd(HIGH_TIM_CH1_GPIO_CLK | HIGH_TIM_CH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
	//通用配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// 输出比较通道1 GPIO 初始化
	GPIO_InitStructure.GPIO_Pin =  HIGH_TIM_CH1_PIN;
	GPIO_Init(HIGH_TIM_CH1_PORT, &GPIO_InitStructure);
	
	// 输出比较通道2 GPIO 初始化	
	GPIO_InitStructure.GPIO_Pin =  HIGH_TIM_CH2_PIN;
	GPIO_Init(HIGH_TIM_CH2_PORT, &GPIO_InitStructure);
	
}


///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)
static void TIM_PWM_HARDWARE_Config(void)
{
	
/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为10K
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	// 占空比配置
	uint16_t CCR1_Val = 1000;
	uint16_t CCR2_Val = 1000;

	
	// 开启定时器时钟,即内部时钟CK_INT=72M
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=HIGH_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= HIGH_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=0;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(HIGH_TIM, &TIM_TimeBaseStructure);


	//启用ARR的影子寄存器 (直到产生更新事件才更改设置)
	TIM_ARRPreloadConfig(HIGH_TIM, ENABLE);
	
	/*--------------------输出比较结构体初始化-------------------*/	
		
	
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OC1Init(HIGH_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(HIGH_TIM, TIM_OCPreload_Enable);	//启用CCR1寄存器的影子寄存器 (直到产生更新时间才更改设置)
	
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
    
//	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC2Init(HIGH_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(HIGH_TIM, TIM_OCPreload_Enable);	//启用CCR2寄存器的影子寄存器 (直到产生更新时间才更改设置)
	

	
	//死区设置      
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;     
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;     
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;     
	TIM_BDTRInitStructure.TIM_DeadTime = 0x90;  //这里调整死区大小0-0xff 
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;      
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;      
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;     
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure); 
	
	// 使能计数器
	TIM_Cmd(HIGH_TIM, ENABLE);
	//TIM1_OC通道输出PWM（一定要加）
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void TIM_PWM_Init(void)
{
	TIM_PWM_GPIO_Config();
	TIM_PWM_HARDWARE_Config();	
}

/***Interface--for motor**************************************/
void motorA_PWM_CTR(uint16_t cnt)
{
	if(cnt>HIGH_TIM_Period)
		cnt = HIGH_TIM_Period;

	HIGH_TIM->CCR1 = cnt;
}
void motorB_PWM_CTR(uint16_t cnt)
{
	if(cnt>HIGH_TIM_Period)
		cnt = HIGH_TIM_Period;

	HIGH_TIM->CCR2 = cnt;
}

