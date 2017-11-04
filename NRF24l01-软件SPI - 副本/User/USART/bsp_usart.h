#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h" 
#include <stdio.h>
//魔术棒 Target  .勾上 Use MicroLIB	\
	可用 printf() scanf() getchar()
/***************************************************************************/
#define USARTx										USART2
#define USARTx_CLK									RCC_APB1Periph_USART2
#define USARTx_BAUDRATE								115200

#define USARTx_GPIO_TX_PORT							GPIOA
#define USARTx_GPIO_TX_CLK							RCC_APB2Periph_GPIOA
#define USARTx_GPIO_TX_PIN							GPIO_Pin_2

#define USARTx_GPIO_RX_PORT							GPIOA
#define USARTx_GPIO_RX_CLK							RCC_APB2Periph_GPIOA
#define USARTx_GPIO_RX_PIN							GPIO_Pin_3

//#define USARTx_IRQHandler            	  USART1_IRQHandler
//#define USARTx_IRQ											USART1_IRQn
/***************************************************************************/

void USART__Init(void);
#endif
