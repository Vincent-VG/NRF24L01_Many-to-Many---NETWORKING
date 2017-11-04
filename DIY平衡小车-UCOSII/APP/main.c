
#include "includes.h"
#include "systick.h"
#include "bsp_led.h"    
#include "bsp_key.h"
#include "./USART/bsp_usart.h"
#include "bsp_motor.h"
#include "bsp_tim_pwm.h"
#include "bsp_tim_encode.h"
#include "SPI/bsp_spi.h"    
#include "OLED/oled.h"  
#include "NRF/nrf.h"

extern unsigned char BMP3[];
extern unsigned char BMP2[];
extern unsigned char BMP1[];

//START ����
//�����������ȼ�
#define START_TASK_PRIO			10  ///��ʼ��������ȼ�Ϊ���
//���������ջ��С
#define START_STK_SIZE			128
//���������ջ
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO			7
//���������ջ��С
#define LED0_STK_SIZE			128
//�����ջ
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);

//LED1����
//�����������ȼ�
#define LED1_TASK_PRIO			6
//���������ջ��С
#define LED1_STK_SIZE			128
//�����ջ
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *pdata);

//KEY����
//�����������ȼ�
#define KEY1_TASK_PRIO			5
//���������ջ��С
#define KEY1_STK_SIZE			128
//�����ջ
OS_STK KEY1_TASK_STK[KEY1_STK_SIZE];
//������
void key1_task(void *pdata);

//ENCODE����
//�����������ȼ�
#define ENCODE_TASK_PRIO		4
//���������ջ��С
#define ENCODE_STK_SIZE			128
//�����ջ
OS_STK ENCODE_TASK_STK[ENCODE_STK_SIZE];
//������
void Encode_Task(void *pdata);

void Init_All() 
{
//	LED_Init();  			//LED��ʼ��
	USART__Init();
//	Motor_Controller_Init();
//	TIM_PWM_Init();
	KEY_Init();
//	TIM_Encode_Init();	
    OLED_Init();
    
    NRF_IO_Init();
    Check_NRF();
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�жϷ�������
	OSInit();  				//UCOS��ʼ��
	
	OSTaskCreate(start_task,(void*)0,
				(OS_STK*)&START_TASK_STK[START_STK_SIZE-1],
				START_TASK_PRIO); //������ʼ����
				
	OSStart(); 				//��ʼ����
	return 0;
}





//��ʼ����
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata=pdata;

    
    
	OS_ENTER_CRITICAL();  		//�����ٽ���(�ر��ж�)

    
    Init_All();
    
    
	Systick_initial();			//����ʱ�ӳ�ʼ��	
	OSStatInit();  				//����ͳ������
	
	OSTaskCreate(led0_task,(void*)0,
				(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],
				LED0_TASK_PRIO);//����LED0����
	OSTaskCreate(led1_task,(void*)0,
				(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],
				LED1_TASK_PRIO);//����LED1����
	OSTaskCreate(key1_task,(void*)0,
				(OS_STK*)&KEY1_TASK_STK[KEY1_STK_SIZE-1],
				KEY1_TASK_PRIO);//
    OSTaskCreate(Encode_Task,(void*)0,
				(OS_STK*)&ENCODE_TASK_STK[ENCODE_STK_SIZE-1],
				ENCODE_TASK_PRIO);//
    
	OSTaskDel(OS_PRIO_SELF);
	
	
	
	OS_EXIT_CRITICAL();  //�˳��ٽ���(���ж�)
}
 

//LED0����
void led0_task(void *pdata)
{
	
	while(1)
	{		
		LED1_OFF; 
		OSTimeDlyHMSM(0,0,0,80);
		LED1_ON;
		OSTimeDlyHMSM(0,0,0,400);				
	}
}

//LED1����
void led1_task(void *pdata)
{
	
	while(1)
	{
		LED2_OFF;
		OSTimeDlyHMSM(0,0,0,1000);
		LED2_ON;
		OSTimeDlyHMSM(0,0,0,1000);
	}
	
}

//key1����
void key1_task(void *pdata)
{
    uint8_t status, sta1, temp;
    char buf[33];
    
	for(;;)
	{
//		OSTimeDlyHMSM(0,0,0,20);
        RX_Mode_Config();

		status = SPI_Read(STATUS);
        SPI_WR_Reg(CMD_FLUSH_RX, 0x01);
		sta1 = SPI_Read(FIFO_STATUS);
		printf("STATUS: 0x%x\n",status);
		printf("FIFO-STATUS: 0x%x\n",sta1);
		
        printf("start receive\n");

        if (status & RX_OK) {
            printf("Successfully receive data\t");
            printf("current STATUS:0x%d\n",status);
            temp = L01_ClearIRQ(RX_OK);   //clear RX IRQ flag
            printf("clear flag...\t");
            printf("current STATUS:0x%d\n",temp);
            
            SPI_Read_Buf(CMD_RD_RX_PLOAD, (unsigned char *)buf, 32);
            printf("Messages:%s\n\n",buf);
            
            L01_ClearIRQ(RX_OK);
            printf("��־������\n");
        }
        else {
            
            printf("��δ���յ����� ,�ȴ���\n");
            
            while (!(status & RX_OK)) {
                status = SPI_Read(CMD_READ_REG | STATUS);
            }
            printf("���յ�����, ƥ����..\n");
            SPI_Read_Buf(CMD_RD_RX_PLOAD, (unsigned char *)buf, 32);
            printf("Messages:%s\n\n",buf);
            if (TryMode_Change(buf) == 1) {
                printf("ƥ��ɹ� ģʽ�л����\n");
                while(1);
            }
            else {
                printf("ģʽ�л�ʧ��\n");
            }
            
        }
	}
}

//2����
void Encode_Task(void *pdata)
{  
	for(;;)
	{   
		OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//??6*8??
		OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//??8*16??
		OSTimeDlyHMSM(0,0,3,3000);
		OLED_CLS();//??
        OSTimeDlyHMSM(0,0,2,3000);
        OLED_Fill(0xf0);
		OSTimeDlyHMSM(0,0,3,0);
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP2);//??BMP????
		OSTimeDlyHMSM(0,0,3,0);
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//??BMP????
        OSTimeDlyHMSM(0,0,3,0);
        OLED_CLS();//??
	}
}






