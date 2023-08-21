#ifndef _delay_H
#define _delay_H

#include <stm32f10x.h>

/*
*Parameter:SysClk
*					ϵͳʱ��Ƶ�ʣ���AHBԤ��Ƶ���ʱ��
*Role     :
*         ��ȷ��ʱ��ʼ��
*/
void SysTick_Init(uint8_t SysClk);
/*
*Parameter:Time
*					usʱ��
*Role     :
*         ��ʱ������us
*/
void Rough_DelayUs(uint16_t Time);
/*
*Parameter:Time
*					msʱ��
*Role     :
*         ��ʱ������ms
*/
void Rough_DelayMs(uint16_t Time);
/*
*Parameter:Time
*					usʱ��(1800,000)
*Role     :
*         ��ʱ������us
*/
void Correct_DelayUs(uint32_t Time);
/*
*Parameter:Time
*					msʱ��(1800)
*Role     :
*         ��ʱ������ms
*/
void Correct_DelayMs(uint16_t Time);

#endif
