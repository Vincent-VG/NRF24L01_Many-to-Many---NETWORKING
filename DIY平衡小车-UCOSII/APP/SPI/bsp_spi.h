#ifndef __BSP_SPI_H
#define __BSP_SPI_H
#include "stm32f10x.h"
#include "stm32f10x_spi.h"

/*GYC***2017*10*29*Version:1.6
**PS:进行(OLED)移植时 所有(最多)需修改项如下;
						1--引脚连接,
						2--SPI_Periphral [static void Simulate_SPI_GPIO_Config(void)],
						
*/


/******************************Hardware***********************************************/

/*****移植时需要修改************************************/
#define OLED_SPIx                   SPI2
#define OLED_SPIx_CLK               RCC_APB1Periph_SPI2

#define OLED_CS_GPIO_PORT           GPIOB
#define OLED_CS_GPIO_PIN            GPIO_Pin_12
#define OLED_CS_GPIO_CLK            RCC_APB2Periph_GPIOB

#define OLED_RST_GPIO_PORT          GPIOB
#define OLED_RST_GPIO_PIN           GPIO_Pin_14
#define OLED_RST_GPIO_CLK           RCC_APB2Periph_GPIOB

#define OLED_DC_GPIO_PORT           GPIOC
#define OLED_DC_GPIO_PIN            GPIO_Pin_6
#define OLED_DC_GPIO_CLK            RCC_APB2Periph_GPIOC

#define OLED_SCLK_GPIO_PORT         GPIOB
#define OLED_SCLK_GPIO_PIN          GPIO_Pin_13
#define OLED_SCLK_GPIO_CLK          RCC_APB2Periph_GPIOB

#define OLED_MOSI_GPIO_PORT         GPIOB
#define OLED_MOSI_GPIO_PIN          GPIO_Pin_15
#define OLED_MOSI_GPIO_CLK          RCC_APB2Periph_GPIOB


/*OLED相关宏定义***无需修改*/
#define OLED_CS_L  	    OLED_CS_GPIO_PORT->BRR=OLED_CS_GPIO_PIN
#define OLED_CS_H  	    OLED_CS_GPIO_PORT->BSRR=OLED_CS_GPIO_PIN
#define	OLED_RST_L	    OLED_RST_GPIO_PORT->BRR=OLED_RST_GPIO_PIN
#define	OLED_RST_H	    OLED_RST_GPIO_PORT->BSRR=OLED_RST_GPIO_PIN
#define OLED_DC_L	    OLED_DC_GPIO_PORT->BRR=OLED_DC_GPIO_PIN
#define OLED_DC_H	    OLED_DC_GPIO_PORT->BSRR=OLED_DC_GPIO_PIN


#define	OLED_SCLK_L	    OLED_SCLK_GPIO_PORT->BRR=OLED_SCLK_GPIO_PIN
#define	OLED_SCLK_H	    OLED_SCLK_GPIO_PORT->BSRR=OLED_SCLK_GPIO_PIN
#define OLED_MOSI_L	    OLED_MOSI_GPIO_PORT->BRR=OLED_MOSI_GPIO_PIN
#define OLED_MOSI_H	    OLED_MOSI_GPIO_PORT->BSRR=OLED_MOSI_GPIO_PIN
/***end**************************************************************************/


/*******************************Clare*****************************************/
//初始化
void xSPI_Init(void);

//OLED----API---Interface---
void WriteCmd(unsigned char Command);
void WriteDat(unsigned char Data);
/***end*****************************************************************************/












#define OLED_CLK    PAout(4)    // CLK??    d0
#define OLED_MOSI   PAout(3)    // MOSI     d1
#define OLED_RST    PAout(2)    // RET??    ret
#define OLED_DC     PAout(1)    // ??|??    dc  (0?????1?????)









/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/* 定义SPI1的GPIO端口 */
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

//NRF附带IO
#define NRF_CE_GPIO_PORT    	GPIOC		          
#define NRF_CE_GPIO_CLK 	   	RCC_APB2Periph_GPIOC 	
#define NRF_CE_GPIO_PIN			GPIO_Pin_5			       

#define NRF_IRQ_GPIO_PORT    	GPIOC			           
#define NRF_IRQ_GPIO_CLK 	    RCC_APB2Periph_GPIOC 	
#define NRF_IRQ_GPIO_PIN		GPIO_Pin_4		       



/***API**************************************************************************/
/*NRF相关宏定义***方便升级移植*/
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

/****************************************************************************************************/
/****************************************************************************************************/
/***end**************************************************************************/




#endif	//(bsp_spi.h)
