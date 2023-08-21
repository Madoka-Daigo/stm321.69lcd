#include "delay.h"

static uint8_t us=0;
static uint16_t ms=0;

//粗延时函数，微秒
void Rough_DelayUs(uint16_t Time)
{    
   uint16_t i=0;  
   while(Time--)
   {
      i=10;  //自己定义
      while(i--) ;    
   }
}
//粗毫秒级的延时
void Rough_DelayMs(uint16_t Time)
{    
   uint16_t i=0;  
   while(Time--)
   {
      i=12000;  //自己定义
      while(i--) ;    
   }
}
//精确延时初始化
void SysTick_Init(uint8_t SysClk)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	us=SysClk/8;
	ms=us*1000;
}
//精确延时函数，微秒
void Correct_DelayUs(uint32_t Time)
{
	uint32_t temp;	    	 
	SysTick->LOAD=Time*us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}
//精确毫秒级的延时
void Correct_DelayMs(uint16_t Time)
{
	uint32_t temp;		   
	SysTick->LOAD=(u32)Time*ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  
}
