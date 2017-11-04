#include "bsp_key.h"                  // Device header
/*
 *@brief
 */
static void NVIC_EXTI_Config ()
{
	NVIC_InitTypeDef    NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}
/*
 *@brief
 */
static void EXTI_KEY_Config ()
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	//GENERAL config
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		

	//KEY1 config
	EXTI_InitStructure.EXTI_Line = macKEY1_EXTI_LINE;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure);
	//KEY2 config
	EXTI_InitStructure.EXTI_Line = macKEY2_EXTI_LINE;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure);
}
/*
 *@brief
 */
static void KEY_GPIO_Config ()
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*GPIO RCC enable*/
	RCC_APB2PeriphClockCmd( macKEY1_GPIO_CLK | macKEY2_GPIO_CLK, ENABLE); 
	
	/*设置引脚模式为输入*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	
	/*KEY1 config*/
	GPIO_InitStructure.GPIO_Pin = macKEY1_GPIO_PIN;			
	GPIO_Init(macKEY1_GPIO_PORT, &GPIO_InitStructure);	
	/*KEY2 config*/
	GPIO_InitStructure.GPIO_Pin = macKEY2_GPIO_PIN;	
	GPIO_Init(macKEY2_GPIO_PORT, &GPIO_InitStructure);

	/*KEY1-Pin 连接至相应中断线*/
	GPIO_EXTILineConfig(macKEY1_EXTI_PORTSOURCE, macKEY1_EXTI_PINSOURCE);   
	/*KEY2-Pin 连接至相应中断线*/
	GPIO_EXTILineConfig(macKEY2_EXTI_PORTSOURCE, macKEY2_EXTI_PINSOURCE); 
}

/*
 *@brief  Init all about KEY
 */
void KEY_Init ()
{		
	KEY_GPIO_Config();
	EXTI_KEY_Config();
	NVIC_EXTI_Config();
}

///*
// *@brief  Scan key1 station (press or unpress)
// *@reval  return KEY_ON (press).	KEY_OFF (unpress)
// */
//int Key1Scan ()
//{
//	if(GPIO_ReadInputDataBit(macKEY1_GPIO_PORT, macKEY1_GPIO_PIN) == KEY_ON) {
//		return KEY_ON;
//	}
//	else {
//		return KEY_OFF;
//	}
//}

///*
// *@brief  Scan key2 station (press or unpress)
// *@reval  return KEY_ON (press).	KEY_OFF (unpress)
// */
//int Key2Scan ()
//{
//	if(GPIO_ReadInputDataBit(macKEY2_GPIO_PORT, macKEY2_GPIO_PIN) == KEY_ON) {
//		return KEY_ON;
//	}
//	else {
//		return KEY_OFF;
//	}
//}


