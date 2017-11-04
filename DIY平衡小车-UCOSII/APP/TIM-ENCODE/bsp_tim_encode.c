#include "bsp_tim_encode.h"
#include <stdio.h>

int32_t motorA_speed=0;    //���β����ı�����ֵ�Ĳ�ֵ�ľ���ֵ
int32_t motorB_speed=0;

static void TIM2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(TIM2_CH1_GPIO_CLK  | TIM2_CH2_GPIO_CLK , ENABLE);		//RCC	enable
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = TIM2_CH1_GPIO_PIN;
	GPIO_Init(TIM2_CH1_GPIO_PORT, &GPIO_InitStructure);   

	GPIO_InitStructure.GPIO_Pin = TIM2_CH2_GPIO_PIN;
	GPIO_Init(TIM2_CH2_GPIO_PORT, &GPIO_InitStructure);	
}

static void TIM4_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(TIM4_CH1_GPIO_CLK | TIM4_CH2_GPIO_PIN, ENABLE);		//RCC	enable
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = TIM4_CH1_GPIO_PIN;
	GPIO_Init(TIM4_CH1_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = TIM4_CH2_GPIO_PIN;
	GPIO_Init(TIM4_CH2_GPIO_PORT, &GPIO_InitStructure);
}

static void TIM2_Hardeware_Config(void)
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   	

	RCC_APB1PeriphClockCmd(ENCODE1_TIM_CLK, ENABLE);//RCC enable

	TIM_DeInit(ENCODE1_TIM);		//denitializes the TIM registers to their default values
	
	TIM_TimeBaseStructure.TIM_Period = TIM_Period_parameter;  //�趨��������װֵ   TIM2_ARR = 359*4
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //TIM2ʱ��Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;//����ʱ�ӷָ� T_dts = T_ck_int	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ��� 
	//Write to registers
	TIM_TimeBaseInit(ENCODE1_TIM, &TIM_TimeBaseStructure);              
                 
	//Pay attention 
	TIM_EncoderInterfaceConfig(ENCODE1_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	TIM_ICStructInit(&TIM_ICInitStructure);//���ṹ���е�����ȱʡ����
	TIM_ICInitStructure.TIM_ICFilter = 6;  //ѡ������Ƚ��˲��� 
	TIM_ICInit(ENCODE1_TIM, &TIM_ICInitStructure);
	

	TIM_ClearFlag(ENCODE1_TIM, TIM_FLAG_Update);//���TIM2�ĸ��±�־λ
	TIM_ITConfig(ENCODE1_TIM, TIM_IT_Update, ENABLE);//enable update interrupt
	//Reset counter
	ENCODE1_TIM->CNT = 0;//

	TIM_Cmd(ENCODE1_TIM, ENABLE);   //start TIM2

}

static void TIM4_Hardeware_Config(void)
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   	

	RCC_APB1PeriphClockCmd(ENCODE2_TIM_CLK, ENABLE);//RCC enable

	TIM_DeInit(ENCODE2_TIM);		//denitializes the TIM registers to their default values
	
	TIM_TimeBaseStructure.TIM_Period = TIM_Period_parameter;  //�趨��������װֵ   TIM4_ARR = 359*4
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //TIM2ʱ��Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;//����ʱ�ӷָ� T_dts = T_ck_int	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ��� 
	//Write to registers
	TIM_TimeBaseInit(ENCODE2_TIM, &TIM_TimeBaseStructure);              
                 
	//Pay attention 
	TIM_EncoderInterfaceConfig(ENCODE2_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	TIM_ICStructInit(&TIM_ICInitStructure);//���ṹ���е�����ȱʡ����
	TIM_ICInitStructure.TIM_ICFilter = 6;  //ѡ������Ƚ��˲��� 
	TIM_ICInit(ENCODE2_TIM, &TIM_ICInitStructure);
	

	TIM_ClearFlag(ENCODE2_TIM, TIM_FLAG_Update);//���TIM4�ĸ��±�־λ
	TIM_ITConfig(ENCODE2_TIM, TIM_IT_Update, ENABLE);//enable update interrupt
	//Reset counter
	ENCODE1_TIM->CNT = 0;//

	TIM_Cmd(ENCODE2_TIM, ENABLE);   //start TIM2
}




/****������ʱ����-TIM7*****20ms�ж�***************************/
static void TIM7_MeasureSpeed_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
		NVIC_InitTypeDef  NVIC_InitStructure;
	//TIM6 RCC enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = 60000;  //�趨��������װֵ 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71; //TIMʱ��Ԥ��Ƶֵ  72M/(71+1)
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//Write to registers
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure); 
	
	
		
	
	//������2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	//�ж�ԴTIM1
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//ʹ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//Write to registers
	NVIC_Init(&NVIC_InitStructure);
	
	//enable Up interrupt
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); 
	TIM_Cmd(TIM7, ENABLE);   //start TIM
}


void TIM_Encode_Init(void)
{	
	/*!!!˳��!!!*/
	TIM2_GPIO_Config();
	TIM2_Hardeware_Config();	
    
    TIM4_GPIO_Config();
    TIM4_Hardeware_Config();
	TIM7_MeasureSpeed_Config();
}

void Speed_Calculate (void) 
{
    uint8_t temB_TIM_CR1=0, temA_TIM_CR1=0;
    int32_t tempB=0, tempA=0;
    static int32_t cntB=0, cntA=0;
    
    
    //get DIR bit;  0--up, 1--down
    temA_TIM_CR1 = (ENCODE1_TIM->CR1) & 0x10;
    temB_TIM_CR1 = (ENCODE2_TIM->CR1) & 0x10;
    //Difference calculation
    tempA = ENCODE1_TIM->CNT - cntA;
    tempB = ENCODE2_TIM->CNT - cntB;
    //get new cnt value
    cntA = ENCODE1_TIM->CNT;
    cntB = ENCODE2_TIM->CNT;
    
    /*ENCODE1 calculate*/
	if(temB_TIM_CR1) {
        if(tempB <= 0) {
			motorB_speed = tempB;
        }
        else {
			motorB_speed = (TIM_Period_parameter-tempB);
        }
    }
    else {	
        if(tempB >= 0) {
            motorB_speed = tempB;
        }
        else {
            motorB_speed = TIM_Period_parameter+tempB;
        }
    }	
    
    /*��������*/
//    if(motorB_speed>1000  || motorB_speed<-1000) {
//        motorB_speed = 0;
//    }
    
    printf("ENCODE1:%d  ", motorB_speed);
    
    /*ENCODE2 calculate*/
    if(temA_TIM_CR1) {
        if(tempA <= 0) {
			motorA_speed = tempA;
        }
        else {
			motorA_speed = (TIM_Period_parameter-tempA);
        }
    }
    else {	
        if(tempA >= 0) {
            motorA_speed = tempA;
        }
        else {
            motorA_speed = TIM_Period_parameter+tempA;
        }
    }	
    
    /*��������*/
//    if(motorA_speed>1000  || motorA_speed<-1000) {
//        motorA_speed = 0;
//    }
//    
    printf("ENCODE2:%d\n", motorA_speed);
}



	//A speed calculate

	//					if(motorA_speed)
	//						printf("motorA_speed: %d\n", motorA_speed);
	//B speed calculate
//	if(temB_CR1)
//	{
//		if(tempB <= 0)
//			motorB_speed = tempB;
//		else
//			motorB_speed = (TIM_Period_parameter-tempB);
//	}
//	else
//	{
//		if(tempB >= 0)
//			motorB_speed = tempB;
//		else
//			motorB_speed = TIM_Period_parameter+tempB;
//	}
//	if(motorB_speed>100  || motorB_speed<-100)
//		motorB_speed = 0;	
