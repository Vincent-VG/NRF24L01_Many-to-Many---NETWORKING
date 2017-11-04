#include "stm32f10x.h"
#include "./USART/bsp_usart.h"
#include "LED/bsp_led.h"   
#include "SPI/bsp_spi.h"    
#include "Delay/delay.h"
#include "./nrf.h"

int main(void)
{	
	unsigned char status, sta1, temp;
	unsigned char buf[]="Hello GYC this is a test";
	LED_Init();
	USART__Init();
	DelayInit();
	SPI1_Init();
	NRF_IO_Init();
    
    Check_NRF();


    TX_Mode_Config((uint8_t *)DATA_MODE_CHANGE);
	while( 1 )
	{
		LED1_TOGGLE
		
        
		status = SPI_Read(STATUS);
		sta1 = SPI_Read( FIFO_STATUS);
		printf("STATUS: 0x%x\n",status);
		printf("FIFO-STATUS: 0x%x\n",sta1);
		


        if (status & (TX_OK|MAX_TX)) {
            if(status & TX_OK) {
                printf("Successfully send data\t");
            }
            else {
                printf("Error about MAX_TX\t");
            }
            
            printf("current STATUS:%d\n",status);
            temp = L01_ClearIRQ(RX_OK | MAX_TX);   //clear TX IRQ flag
            printf("clear flag...\t");
            printf("current STATUS:%d\n",temp);
            
//            SPI_Read_Buf(CMD_RD_RX_PLOAD, (unsigned char *)buf, 32);
//            printf("Messages:%s\n",buf);
            L01_ClearIRQ(TX_OK | MAX_TX);
            printf("标志位清楚完成\n\n");
            printf("正在尝试模式切换...\n");
            if (TryMode_Change("") == 1) {
                printf("模式切换成功\n");
                while(1);
            }
            else {
                printf("模式切换失败\n\n");
            }
//            while(1);
        }
        else {
            
            printf("数据发送未完成,等待中\n");
            
            while (!(status & (TX_OK|MAX_TX))) {
                status = SPI_Read( STATUS);
            }
        } 

		
        
	}
}

	


