#include "./USART/bsp_usart.h"


//static void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* 嵌套向量中断控制器组选择 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* 配置USART3为中断源 */
//  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQ;
//  /* 抢占优先级为1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* 子优先级为1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 使能中断 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* 初始化配置NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}


static void USART_GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	//使能GPIO时钟
	RCC_APB2PeriphClockCmd(USARTx_GPIO_TX_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(USARTx_GPIO_RX_CLK,ENABLE);
	       
	//通用配置
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//.USARTx TX引脚复用推挽输出
	GPIO_InitStruct.GPIO_Pin = USARTx_GPIO_TX_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USARTx_GPIO_TX_PORT, &GPIO_InitStruct);	//送配置好成员的结构体进寄存器
	//.USARTx RX引脚上拉输入
	GPIO_InitStruct.GPIO_Pin = USARTx_GPIO_RX_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(USARTx_GPIO_RX_PORT, &GPIO_InitStruct);	//送配置好成员的结构体进寄存器	
}

static void USART_Hardware_Config(void)
{
	USART_InitTypeDef	USART_InitStruct;
	
	//RCC-Enable
	RCC_APB1PeriphClockCmd(USARTx_CLK,ENABLE);
	
	//波特率
	USART_InitStruct.USART_BaudRate = USARTx_BAUDRATE;
	//字长:数据位+校验位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	//模式控制	:	同时使能接收与发送
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	//检验控制: 无校验77.0.0.
	USART_InitStruct.USART_Parity = USART_Parity_No;
	//停止位: 1位
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	//硬件流控制: 无
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/*结构体写入寄存器*/
	USART_Init(USARTx, &USART_InitStruct);	//完成USART配置(送结构体至寄存器)
	
//	/* 配置串口接收中断 */
//	NVIC_Configuration();	
//	
//	/* 使能串口接收中断 */
//	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
/* 使能串口 */
  USART_Cmd(USARTx, ENABLE);
}

void USART__Init(void)
{
	/*PS:若初始化顺序颠倒则初次发送会有问题 延时可解决?*/	
	/*  USART硬件初始化*/
	USART_Hardware_Config();
	/*  GPIO初始化 */
	USART_GPIO_Config();	
	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{

    /* 发送一个字节数据到串口 */
    USART_SendData(USARTx, (uint8_t) ch);
    
    /* 等待发送完毕 */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		

    return (ch);
}
//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTx);
}

/*********************************************END OF FILE**********************/

