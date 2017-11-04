#ifndef __BSP_SPI_H
#define __BSP_SPI_H
#include "stm32f10x.h"

/*GYC***2017*8*8*Version:1.0
**PS:����(NRF)��ֲʱ ����(���)���޸�������;
						1--Ӳ������,
						2--����Ӳ��SPI�������,
						3--NRF�궨������.
*/


/******************************Hardware***********************************************/
/*****************************************************************************/
/*Ӳ������(ģ��-SPI)
	MOSI---PA7
	 SCK---PA5
	*/

/*Ӳ������(OLED����IO)
	 RES---PA2
	  DC---PA3
	*/
/***end**************************************************************************/



/* ����SPI1��GPIO�˿� */
#define SPI1_CS_GPIO_PORT    	GPIOA				            
#define SPI1_CS_GPIO_CLK 	   	RCC_APB2Periph_GPIOA		
#define SPI1_CS_GPIO_PIN		GPIO_Pin_4		    

#define SPI1_SCK_GPIO_PORT    	GPIOA			           
#define SPI1_SCK_GPIO_CLK 	    RCC_APB2Periph_GPIOA	
#define SPI1_SCK_GPIO_PIN		GPIO_Pin_5			   	

#define SPI1_MISO_GPIO_PORT    	GPIOA			          
#define SPI1_MISO_GPIO_CLK 	    RCC_APB2Periph_GPIOA 	
#define SPI1_MISO_GPIO_PIN		GPIO_Pin_6			      

#define SPI1_MOSI_GPIO_PORT    	GPIOA			          
#define SPI1_MOSI_GPIO_CLK 	    RCC_APB2Periph_GPIOA 	
#define SPI1_MOSI_GPIO_PIN		GPIO_Pin_7			        

//NRF����IO
#define NRF_CE_GPIO_PORT    	GPIOB	          
#define NRF_CE_GPIO_CLK 	   	RCC_APB2Periph_GPIOB 	
#define NRF_CE_GPIO_PIN			GPIO_Pin_1			       

#define NRF_IRQ_GPIO_PORT    	GPIOB			           
#define NRF_IRQ_GPIO_CLK 	    RCC_APB2Periph_GPIOB 	
#define NRF_IRQ_GPIO_PIN		GPIO_Pin_0		       



/***API**************************************************************************/
/*NRF��غ궨��***����������ֲ*/
#define NRF_CE_L					GPIO_ResetBits(NRF_CE_GPIO_PORT, NRF_CE_GPIO_PIN);
#define NRF_CE_H					GPIO_SetBits(NRF_CE_GPIO_PORT, NRF_CE_GPIO_PIN);
#define SPI_CS_L					GPIO_ResetBits(SPI1_CS_GPIO_PORT, SPI1_CS_GPIO_PIN);
#define SPI_CS_H					GPIO_SetBits(SPI1_CS_GPIO_PORT, SPI1_CS_GPIO_PIN);
#define SPI_SCK_L					GPIO_ResetBits(SPI1_SCK_GPIO_PORT, SPI1_SCK_GPIO_PIN);
#define SPI_SCK_H					GPIO_SetBits(SPI1_SCK_GPIO_PORT, SPI1_SCK_GPIO_PIN);
#define SPI_MOSI_L					GPIO_ResetBits(SPI1_MOSI_GPIO_PORT, SPI1_MOSI_GPIO_PIN);
#define SPI_MOSI_H					GPIO_SetBits(SPI1_MOSI_GPIO_PORT, SPI1_MOSI_GPIO_PIN);
#define SPI_MISO_Sta			GPIO_ReadInputDataBit(SPI1_MISO_GPIO_PORT, SPI1_MISO_GPIO_PIN)
#define NRF_IRQ_Sta				GPIO_ReadInputDataBit(NRF_IRQ_GPIO_PORT, NRF_IRQ_GPIO_PIN)
#define NRF_IRQ_H					GPIO_SetBits(NRF_IRQ_GPIO_PORT, NRF_IRQ_GPIO_PIN);
/***end**************************************************************************/


/*******************************Clare*****************************************/
//��ʼ��
void SPI1_Init(void);
//OLED----API---Interface---
void WriteCmd(unsigned char Command);
void WriteDat(unsigned char Data);
void OLED_RST_Set(void);
void OLED_RST_Clr(void);
/***end*****************************************************************************/



#endif	//(bsp_spi.h)
