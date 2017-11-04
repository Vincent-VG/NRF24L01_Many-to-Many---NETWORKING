#include "led.h"


/************************************************************************************
**����˵����
**1���������LED0��ӦCPU��IO��PB5��
**2���������LED1��ӦCPU��IO��PE5��
**3��IO��Ϊ�͵�ƽʱ��LED����
**4��IO��Ϊ�ߵ�ƽʱ��LED��
**5��ʹ������PB��PE��ʱ�ӣ�����IO��Ϊ�������������50MHz��
**
************************************************************************************/

void led_initial(void)
{
	GPIO_InitTypeDef	GPIO_Init_Struct;//����GPIO��ʼ���ṹ��
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//ʹ������ʱ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	//ʹ������ʱ��
	
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_5;					//IO����Ϊpin5
	
	GPIO_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;			//����Ϊ50MHz
	
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_Out_PP;			//�������
	
	GPIO_Init(GPIOB,&GPIO_Init_Struct);						//��ʼ��PB
	
	GPIO_Init(GPIOE,&GPIO_Init_Struct);						//��ʼ��PE
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);							//��ʼ��������������ߵ�ƽ����LEDΪ��״̬
	
	GPIO_SetBits(GPIOE,GPIO_Pin_5);							//��ʼ��������������ߵ�ƽ����LEDΪ��״̬
	

	
}



