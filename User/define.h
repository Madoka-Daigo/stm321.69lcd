#ifndef _define_H
#define _define_H

#include <stm32f10x.h>

//*define output Level*/
typedef enum
{
	Level_L=0,
	Level_H
}Level;
//*define time unit*/
typedef enum
{
	us=0,
	ms
}Unit;

void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断

#endif
