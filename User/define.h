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

void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�

#endif
