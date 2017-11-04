#include "./USART/bsp_usart.h"


//static void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* Ƕ�������жϿ�������ѡ�� */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* ����USART3Ϊ�ж�Դ */
//  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQ;
//  /* ��ռ���ȼ�Ϊ1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* �����ȼ�Ϊ1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}


static void USART_GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	//ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd(USARTx_GPIO_TX_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(USARTx_GPIO_RX_CLK,ENABLE);
	       
	//ͨ������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//.USARTx TX���Ÿ����������
	GPIO_InitStruct.GPIO_Pin = USARTx_GPIO_TX_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USARTx_GPIO_TX_PORT, &GPIO_InitStruct);	//�����úó�Ա�Ľṹ����Ĵ���
	//.USARTx RX������������
	GPIO_InitStruct.GPIO_Pin = USARTx_GPIO_RX_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(USARTx_GPIO_RX_PORT, &GPIO_InitStruct);	//�����úó�Ա�Ľṹ����Ĵ���	
}

static void USART_Hardware_Config(void)
{
	USART_InitTypeDef	USART_InitStruct;
	
	//RCC-Enable
	RCC_APB1PeriphClockCmd(USARTx_CLK,ENABLE);
	
	//������
	USART_InitStruct.USART_BaudRate = USARTx_BAUDRATE;
	//�ֳ�:����λ+У��λ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	//ģʽ����	:	ͬʱʹ�ܽ����뷢��
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	//�������: ��У��77.0.0.
	USART_InitStruct.USART_Parity = USART_Parity_No;
	//ֹͣλ: 1λ
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	//Ӳ��������: ��
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/*�ṹ��д��Ĵ���*/
	USART_Init(USARTx, &USART_InitStruct);	//���USART����(�ͽṹ�����Ĵ���)
	
//	/* ���ô��ڽ����ж� */
//	NVIC_Configuration();	
//	
//	/* ʹ�ܴ��ڽ����ж� */
//	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
/* ʹ�ܴ��� */
  USART_Cmd(USARTx, ENABLE);
}

void USART__Init(void)
{
	/*PS:����ʼ��˳��ߵ�����η��ͻ������� ��ʱ�ɽ��?*/	
	/*  USARTӲ����ʼ��*/
	USART_Hardware_Config();
	/*  GPIO��ʼ�� */
	USART_GPIO_Config();	
	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{

    /* ����һ���ֽ����ݵ����� */
    USART_SendData(USARTx, (uint8_t) ch);
    
    /* �ȴ�������� */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		

    return (ch);
}
//�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTx);
}

/*********************************************END OF FILE**********************/

