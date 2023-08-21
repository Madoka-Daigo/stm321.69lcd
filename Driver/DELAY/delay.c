#include "delay.h"

static uint8_t us=0;
static uint16_t ms=0;

//����ʱ������΢��
void Rough_DelayUs(uint16_t Time)
{    
   uint16_t i=0;  
   while(Time--)
   {
      i=10;  //�Լ�����
      while(i--) ;    
   }
}
//�ֺ��뼶����ʱ
void Rough_DelayMs(uint16_t Time)
{    
   uint16_t i=0;  
   while(Time--)
   {
      i=12000;  //�Լ�����
      while(i--) ;    
   }
}
//��ȷ��ʱ��ʼ��
void SysTick_Init(uint8_t SysClk)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	us=SysClk/8;
	ms=us*1000;
}
//��ȷ��ʱ������΢��
void Correct_DelayUs(uint32_t Time)
{
	uint32_t temp;	    	 
	SysTick->LOAD=Time*us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	 
}
//��ȷ���뼶����ʱ
void Correct_DelayMs(uint16_t Time)
{
	uint32_t temp;		   
	SysTick->LOAD=(u32)Time*ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	  
}
