#include "./nrf.h"

/*PS:CE为低时一定可读写寄存器*/


/*底层的最基本读写驱动*/
static uint8_t SPI_RW(uint8_t byte)
{
	uint8_t bit_ctr;
	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
	{
		if(byte & 0x80)       // output 'byte', MSB to MOSI
		{
			SPI_MOSI_H
		}
		else
		{
			SPI_MOSI_L
		}
		byte = (byte << 1);   // shift next bit into MSB..
		SPI_SCK_H 			  // Set SCK high..
		byte |= SPI_MISO_Sta; // capture current MISO bit
		SPI_SCK_L			  // ..then set SCK low again
	}
	return(byte);		 // return read byte
}

/*底层基本写寄存器驱动;  返回值为状态寄存器值*/
uint8_t SPI_WR_Reg(uint8_t reg, uint8_t value)
{
	uint8_t status;
	
	SPI_CS_L 			  // CS low, init SPI transaction
	status = SPI_RW(reg); // select register
	SPI_RW(value); 		  // ..and write value to it..
	SPI_CS_H 			  // CS high again
	return(status);		  // return nRF24L01 status byte
}

/*底层基本读寄存器驱动*/
uint8_t SPI_Read(uint8_t reg)
{
	uint8_t reg_val;
	
	SPI_CS_L // CSN low, initialize SPI communication...
	SPI_RW(CMD_READ_REG | reg); // Select register to read from..
	reg_val = SPI_RW(0); // ..then read registervalue	
	SPI_CS_H // CSN high, terminate SPI communication
	
	return(reg_val); // return register value
}
/*底层基本缓冲读驱动*/
uint8_t SPI_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t bytes)
{
	uint8_t status,byte_ctr;
	
	SPI_CS_L 								// Set CSN low, init SPI tranaction	
	status = SPI_RW(reg); 					// Select register to write to and read status byte
	for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
		pBuf[byte_ctr] = SPI_RW(0); 		// Perform SPI_RW to read byte from nRF24L01	
	SPI_CS_H 								// Set CSN high again
	
	return(status); 						// return nRF24L01 status byte
}
/*底层基本缓冲写驱动*/
uint8_t SPI_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t bytes)
{
	uint8_t status,byte_ctr;
	
	SPI_CS_L 									// Set CSN low, init SPI tranaction	
	status = SPI_RW(reg); 						// Select register to write to and read status byte
	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) // then write all byte in buffer(*pBuf)
		SPI_RW(*pBuf++);
	SPI_CS_H 									// Set CSN high again

	return(status); // return nRF24L01 status byte
}

/*0--成功; 1--失败.  有串口输出*/
uint8_t Check_NRF(void)
{
	uint8_t  tempBuf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
	NRF_IO_Init();
	SPI_Write_Buf(CMD_WRITE_REG + TX_ADDR, tempBuf, 5);	//写地址
	SPI_Read_Buf(CMD_READ_REG + TX_ADDR, tempBuf, 5);	//读地址
	for(i=0;i<5;i++)
	{
		if(tempBuf[i]!=0XA5)
			break;	 	
	}
	if(i!=5)
	{
		printf("NRF24L01 check error!\n");
		return 1;//检测失败 
	}
	else
	{
		printf("NRF24L01 check succussful!\n");
		return 0;		 
	}
	
}

/**************************************************------------------------------------------

 这个函数设置nRF24L01为接收模式，等待接收发送设备的数据包
**************************************************/


/*
================================================================================
Function : L01_ClearIRQ( )
Description : Clear IRQ cuased by nRF24L01
Input : None
Output: None
================================================================================
*/
uint8_t L01_ClearIRQ( uint8_t IRQ_Source )
{
    uint8_t btmp = 0;

    NRF_CE_L
    
    IRQ_Source &=  (RX_OK | TX_OK | MAX_TX);
    
    btmp = SPI_WR_Reg(CMD_NOP,0);
    btmp = SPI_WR_Reg(CMD_WRITE_REG + STATUS, IRQ_Source | btmp);
    
    return btmp;
}

void NRF_IO_Init(void)
{
	SPI_CS_H
	NRF_CE_L
	SPI_SCK_L
	NRF_IRQ_H
    
    L01_ClearIRQ(RX_OK | TX_OK | MAX_TX);
    SPI_WR_Reg(CMD_FLUSH_RX, 0);
    SPI_WR_Reg(CMD_FLUSH_TX, 0);
}

void Mode_PowerDown(void)
{
	uint8_t temp;		//为了只修改寄存器的两位
	NRF_CE_L
	temp = SPI_Read(CMD_READ_REG + CONFIG);	//获取当前寄存器配置
	SPI_WR_Reg(CMD_WRITE_REG + CONFIG, (temp&0xfc)|0x00);	//掉电 发射模式 其余保持不变
}

void Mode_Standby1(void)
{
	uint8_t temp;		//为了只修改寄存器的位
	NRF_CE_L
	temp = SPI_Read(CMD_READ_REG + CONFIG);	//获取当前寄存器配置
	SPI_WR_Reg(CMD_WRITE_REG + CONFIG , (temp&0xfc)|0x02);	//上电 发射模式(也可接收模式) 其余保持不变
}

/*必须TX FIFO为空 才可能处于待机模式二*/
void Mode_Standby2(void)
{
	uint8_t temp;		//为了只修改寄存器的两位
	NRF_CE_L
	SPI_RW(CMD_FLUSH_TX);  //clear TX FIFO
	temp = SPI_Read(CMD_READ_REG + CONFIG);	//获取当前寄存器配置
	SPI_WR_Reg(CMD_WRITE_REG + CONFIG, (temp&0xfc)|0x02);	//上电 发射模式 其余保持不变
	NRF_CE_H
}

void Mode_RX(void)
{
	uint8_t temp;		//为了只修改寄存器的两位
	NRF_CE_L
	temp = SPI_Read(CMD_READ_REG + CONFIG);	//获取当前寄存器配置
	SPI_WR_Reg(CMD_WRITE_REG + CONFIG, (temp&0xfc)|0x03);	//上电 接收模式 其余保持不变
	NRF_CE_H
}

void Mode_TX(void)
{
	Mode_Standby1();
	NRF_CE_H
	DelayUs(13);
}




void RX_Mode_Config(void)
{
	NRF_CE_L
    
    SPI_WR_Reg(CMD_FLUSH_RX, 0);
	//默认为五字节地址宽度
  	SPI_Write_Buf(CMD_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // 接收设备接收通道0使用和发送设备相同的发送地址
  	SPI_WR_Reg(CMD_WRITE_REG + EN_AA, 0x01);               // 使能接收通道0自动应答
  	SPI_WR_Reg(CMD_WRITE_REG + EN_RXADDR, 0x01);           // 使能接收通道0
  	SPI_WR_Reg(CMD_WRITE_REG + RF_CH, 40);                 // 选择射频通道0x40
  	SPI_WR_Reg(CMD_WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);  // 接收通道0选择和发送通道相同有效数据宽度
  	SPI_WR_Reg(CMD_WRITE_REG + RF_SETUP, 0x07);            // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
  	SPI_WR_Reg(CMD_WRITE_REG + CONFIG, 0x0f);              // CRC使能，16位CRC校验，上电，接收模式

	NRF_CE_H                                            // 拉高CE启动接收设备

}
/**************************************************/
/**************************************************
    这个函数设置nRF24L01为发送模式，（CE=1持续至少10us），
	130us后启动发射，数据发送结束后，发送模块自动转入接收
	模式等待应答信号。
**************************************************/
void TX_Mode_Config(uint8_t * BUF)
{
	NRF_CE_L
    
    SPI_WR_Reg(CMD_FLUSH_TX, 0);
	//默认为五字节地址宽度
  	SPI_Write_Buf(CMD_WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // 写入发送地址
  	SPI_Write_Buf(CMD_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // 为了应答接收设备，接收通道0地址和发送地址相同
  	SPI_Write_Buf(CMD_WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH);                  // 写数据包到TX FIFO
  	SPI_WR_Reg(CMD_WRITE_REG + EN_AA, 0x01);       // 使能接收通道0自动应答
  	SPI_WR_Reg(CMD_WRITE_REG + EN_RXADDR, 0x01);   // 使能接收通道0
  	SPI_WR_Reg(CMD_WRITE_REG + SETUP_RETR, 0x0a);  // 自动重发延时等待250us+86us，自动重发10次
  	SPI_WR_Reg(CMD_WRITE_REG + RF_CH, 40);         // 选择射频通道0x40
  	SPI_WR_Reg(CMD_WRITE_REG + RF_SETUP, 0x07);    // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	SPI_WR_Reg(CMD_WRITE_REG + CONFIG, 0x0e);      // CRC使能，16位CRC校验，上电 发送模式
	
	NRF_CE_H
	DelayUs(13);	//  >10us
}

/*
 *@brief 在发送或接收模式下 尝试协调双方进行模式转变(主 从),
 *       若失败则维持原主从角色            PS:需自动应答使能
 *@Parameter 接收到的字符串(在发送模式下)
 *@reval 0-error  1-success
 */
uint8_t TryMode_Change(char *pBuf) 
{
    uint8_t temp, cnt;
    /*应可读写寄存器*/
    NRF_CE_L

    temp = SPI_Read(CONFIG);
    /*判断是否为接收模式*/
    if (temp & PRIM_RX ) {

        L01_ClearIRQ(TX_OK | MAX_TX | RX_OK);
        
        if (strcmp(pBuf, DATA_MODE_CHANGE) == 0) {  //确认为模式转变命令
            NRF_CE_L
            printf("active \n");
            SPI_WR_Reg(CMD_FLUSH_TX, 0);
            SPI_WR_Reg(CMD_FLUSH_RX, 0);

            TX_Mode_Config((uint8_t *)MODE_CHANGE_OK);
            
            return 1;
//            cnt = 99;
//            while (cnt--) {
//                
//                temp = SPI_Read( STATUS);
//            
//                if (temp & TX_OK) {     //转换成功
//                    L01_ClearIRQ(TX_OK | MAX_TX);
//                    printf("really OK\n");
//                    return 1;
//                }
//                else {                    
//                    L01_ClearIRQ(MAX_TX);                 
//                    if(cnt == 0) {      //转换失败
//                        RX_Mode_Config();                  
//                        return 0;
//                    }
//                }
//            }
        }
        else {
            printf("1111\n");
            return 0;
        }
    }
    
    /*发送模式时*/
    else {
        L01_ClearIRQ(MAX_TX | TX_OK | RX_OK);
        TX_Mode_Config((uint8_t *)DATA_MODE_CHANGE);
        temp = SPI_Read(FIFO_STATUS);
        printf("send CONFIG:0x%x ", temp);
        cnt = 255;
        while (cnt--) {
            
            temp = SPI_Read(STATUS);
            printf("status status:0x%x ", temp);
            if (temp & TX_OK) {
                L01_ClearIRQ(TX_OK | MAX_TX | RX_OK);
                
                printf("active stm8\n");
                
                RX_Mode_Config();
                
                return 1;
//                DelayMs(1000);
//                temp = SPI_Read(CMD_READ_REG | STATUS);
//                if (temp & RX_OK) {     //模式转变成功
//                    L01_ClearIRQ(RX_OK);
//                    printf("really oK\n");
//                    return 1;
//                }
//                else {      //模式转变失败
//                    SPI_WR_Reg(CMD_FLUSH_TX, 0); 
//                    SPI_WR_Reg(CMD_WRITE_REG + CONFIG, 0x0e);      // CRC使能，16位CRC校验，上电 发送模式
//                    NRF_CE_H
//                    DelayUs(13);	//  >10us
//                    
//                    return 0;
//                }
            }
            else {                    
                L01_ClearIRQ(MAX_TX | RX_OK);                 
                if(cnt == 0) {
                    return 0;
                }
            }
        }     
    }  
    return 0;
}

/*前提:NRF已配置好为发送模式
返回值为标志位 若不是则为不可能错误!
*/
uint8_t NRF_TXPacket(uint8_t *pBuf)
{
	uint8_t sta;
	NRF_CE_L
	SPI_WR_Reg( CMD_WRITE_REG + STATUS, 0xff);	//clear all flag
	SPI_Write_Buf(CMD_WR_TX_PLOAD, pBuf, TX_PLOAD_WIDTH);//write data to be send
	Mode_TX();	//start send
	while(NRF_IRQ_Sta);	//wait interrupt
	sta = SPI_RW(CMD_NOP);	//read STATUS register
	if(sta & MAX_TX)
	{
		SPI_RW(CMD_FLUSH_TX);	//clear TX_FIFO  
		SPI_WR_Reg( CMD_WRITE_REG + STATUS, 0xff);	//clear all flag
		printf("NRF_TX_Error:  Get MAX_TX flag\n");
		return MAX_TX;
	}
	else if (sta & TX_OK)
	{
		SPI_WR_Reg( CMD_WRITE_REG + STATUS, 0xff);	//clear all flag
		printf("\tNRF has Send successfuly!\n");
		return TX_OK;
	}
	else 
		printf("\t!!!a error that can't happen [NRF]!!!\n");
	return 0;
}

/*前提:NRF已配置好为接收模式
reval:  RX_OK--success		0--error
*/
uint8_t NRF_RXPacket(uint8_t *pBuf)
{
	uint8_t sta;

	sta = SPI_RW(CMD_NOP);	//read STATUS register

	if (sta & RX_OK)
	{
		SPI_Read_Buf(CMD_RD_RX_PLOAD,pBuf,TX_PLOAD_WIDTH);
		SPI_WR_Reg( CMD_WRITE_REG + STATUS, 0xff);	//clear all flag
		printf("\tNRF has Read successfuly!\n");
		return RX_OK;
	}
	else 
		return 0;
}




