#ifndef __NRF_H
#define __NRF_H
#include "stm32f10x.h"
#include "stdio.h"
#include <string.h>
#include "includes.h"
/***Start***Interface***Security****************************************************************/
/***/
#include "bsp_spi.h"
	/*---API---*/
	//	#define NRF_CE_L
	//	#define NRF_CE_H	
	//	#define SPI_CS_L
	//	#define SPI_CS_H
	//	#define SPI_SCK_L
	//	#define SPI_SCK_H
	//	#define SPI_MOSI_L
	//	#define SPI_MOSI_H
	//	#define SPI_MISO_Sta
	//	#define NRF_IRQ_Sta
	//	NRF_IRQ_H
/***/
/***/
//#include "Delay/delay.h" 
	/*---API---*/
	//void DelayMs(unsigned int nms);
/***/
/***End***Interface***Security*****************************************************************/


/***Function****/

uint8_t SPI_WR_Reg(uint8_t reg, uint8_t value);
uint8_t SPI_Read(uint8_t reg);
uint8_t SPI_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t bytes);
uint8_t SPI_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t bytes);

uint8_t L01_ClearIRQ( uint8_t IRQ_Source );

void TX_Mode_Config(uint8_t * BUF);
void RX_Mode_Config(void);
void Mode_PowerDown(void);
void Mode_Standby1(void);
void Mode_Standby2(void);
void Mode_RX(void);
uint8_t NRF_TXPacket(uint8_t *pBuf);
uint8_t NRF_RXPacket(uint8_t *pBuf);
uint8_t Check_NRF(void);
void NRF_IO_Init(void);

uint8_t TryMode_Change(char *pBuf);

#define DATA_MODE_CHANGE     "start-mode-change-TR"
#define MODE_CHANGE_OK       "mode-change-OK"

#define TX_ADR_WIDTH   5  //  address width
#define TX_PLOAD_WIDTH 32  // data width
static  uint8_t TX_ADDRESS[5] = {0x30,0x17,0x02,0x17,0x02};  // 

// SPI(nRF24L01) commands
#define CMD_READ_REG   	0x00  // Define read command to register
#define CMD_WRITE_REG   0x20  // Define write command to register
#define CMD_RD_RX_PLOAD 0x61  // Define RX payload register address
#define CMD_WR_TX_PLOAD 0xA0  // Define TX payload register address
#define CMD_FLUSH_TX    0xE1  // Define flush TX register command
#define CMD_FLUSH_RX    0xE2  // Define flush RX register command
#define CMD_REUSE_TX_PL 0xE3  // Define reuse TX payload register command
#define CMD_NOP         0xFF  // Define No Operation, might be used to read status register

//NRF Flag   [in STATUS Register]
#define MAX_TX  		0x10  //最大重发次数
#define TX_OK   		0x20  //发送完成
#define RX_OK   		0x40  //接收标志
#define PWR_UP  		0x02  //上电
#define PRIM_RX   		0x01  //接收模式

// SPI(nRF24L01) registers(addresses)
#define CONFIG      0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    0x03  // 'Setup address width' register address
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address


#endif //(nrf.h)
