#ifndef __OLED_H
#define __OLED_H
/*GYC***2017*10*29*Version:1.6*/
//Source:野火  仅适用ssd1306的驱动???
//Under SPI  Only Write
//***IIC***#define OLED_ADDRESS	0x78		//0R 0x78 or 0x7a   ---default 0x78


/* 
*@@@brief 移植时只需要提供以下 API函数 即可
 */

#define Start_Position	1	//1--正向 0---反向

/***Start***Interface***Security****************************************************************/

/***/
#include "SPI/bsp_spi.h"

#define OELD_SPI_Init()     xSPI_Init()

	/*---API---*/
	//1. void WriteCmd(unsigned char Command); PS: 8bit(MSB)  //DC[L]
	//2. void WriteDat(unsigned char Data);    PS: 8bit(MSB)  //DC[H]

/***/

/***End***Interface***Security*****************************************************************/




void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif	//(oled.h)
