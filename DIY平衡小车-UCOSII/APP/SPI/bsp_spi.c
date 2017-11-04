#include "bsp_spi.h"                  // Device header

static void SPI2_GPIO_Config (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(OLED_SCLK_GPIO_CLK |
                           OLED_MOSI_GPIO_CLK |
                           OLED_CS_GPIO_CLK |                       
                           OLED_DC_GPIO_CLK |
                           OLED_RST_GPIO_CLK , ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_SCLK_GPIO_PIN;				    //SPI2-SCK	
	GPIO_Init(OLED_SCLK_GPIO_PORT, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_MOSI_GPIO_PIN;			//SPI2-MOSI
	GPIO_Init(OLED_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_CS_GPIO_PIN;				//CS
	GPIO_Init(OLED_CS_GPIO_PORT, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_DC_GPIO_PIN;				//DC
	GPIO_Init(OLED_DC_GPIO_PORT, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_RST_GPIO_PIN;			//RST
	GPIO_Init(OLED_RST_GPIO_PORT, &GPIO_InitStructure);
}

static void SPI2_Periphral_Config(void)
{
    SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(OLED_SPIx, &SPI_InitStructure);
	
	SPI_Cmd(OLED_SPIx, ENABLE);
}

static void SPI1_GPIO_Config(void)
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

void xSPI_Init(void)
{
    /*SPI2 for OLED*/
	SPI2_GPIO_Config();
    SPI2_Periphral_Config();
    /*SPI1 for NRF*/
    SPI1_GPIO_Config();
    NRF_IRQ_CE_GPIO_Config();
}


/*************************************************************************/
/*OLED--API---й╣ож                                                       */
/*************************************************************************/
static void SPI_OLED_WriteByte(unsigned char data,unsigned char cmdORdat)
{
    u8 i=2;
	
	if(cmdORdat)	
        OLED_DC_H;
	else 	
        OLED_DC_L;
	
	while (SPI_I2S_GetFlagStatus(OLED_SPIx, SPI_I2S_FLAG_TXE) == RESET);
    
	SPI_I2S_SendData(OLED_SPIx, data);
    
	while(i--);		
}

void WriteCmd(unsigned char Command)
{
    SPI_OLED_WriteByte(Command,0);
}
void WriteDat(unsigned char Data)
{
    SPI_OLED_WriteByte(Data,1);
}


/*************************************************************************/
/*************************************************************************/

