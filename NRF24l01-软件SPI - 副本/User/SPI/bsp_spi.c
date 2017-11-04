#include "bsp_spi.h"                  // Device header

static void SPI_GPIO_Config(void)
{		

	
	GPIO_InitTypeDef GPIO_InitStructure;

	/*RCC---ENABLE*/
	RCC_APB2PeriphClockCmd(SPI1_CS_GPIO_CLK  	|
												 SPI1_SCK_GPIO_CLK 	|
												 SPI1_MISO_GPIO_CLK |
												 SPI1_MOSI_GPIO_CLK, ENABLE);  

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	//CS---Pin									   
	GPIO_InitStructure.GPIO_Pin = SPI1_CS_GPIO_PIN;	
	/**/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	/**/
	GPIO_Init(SPI1_CS_GPIO_PORT, &GPIO_InitStructure);	
	

	
	//SCK---Pin										   
	GPIO_InitStructure.GPIO_Pin = SPI1_SCK_GPIO_PIN;	
	/**/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	/**/
	GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStructure);
	

	
	//MOSI---Pin										   
	GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_GPIO_PIN;	
	/**/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	/**/
	GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
	//MISO---Pin										   
	GPIO_InitStructure.GPIO_Pin = SPI1_MISO_GPIO_PIN;	
	/**/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	/**/
	GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStructure);
}
/*NRF  IRQ & CE Pin*/
static void NRF_IRQ_CE_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*RCC---ENABLE*/
	RCC_APB2PeriphClockCmd(NRF_CE_GPIO_CLK	| NRF_IRQ_GPIO_CLK, ENABLE);  

	/* */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/**/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//CE--Pin					   
	GPIO_InitStructure.GPIO_Pin = NRF_CE_GPIO_PIN;	  
	/**/
	GPIO_Init(NRF_CE_GPIO_PORT, &GPIO_InitStructure);	
	
	NRF_CE_H
	
	//IRQ--Pin					   
	GPIO_InitStructure.GPIO_Pin = NRF_IRQ_GPIO_PIN;	 
	/**/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/**/
	GPIO_Init(NRF_IRQ_GPIO_PORT, &GPIO_InitStructure);
}


void SPI1_Init(void)
{
	NRF_IRQ_CE_GPIO_Config();
	SPI_GPIO_Config();
}

















