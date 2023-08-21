#ifndef _delay_H
#define _delay_H

#include <stm32f10x.h>

/*
*Parameter:SysClk
*					系统时钟频率，即AHB预分频后的时钟
*Role     :
*         精确延时初始化
*/
void SysTick_Init(uint8_t SysClk);
/*
*Parameter:Time
*					us时间
*Role     :
*         延时参数个us
*/
void Rough_DelayUs(uint16_t Time);
/*
*Parameter:Time
*					ms时间
*Role     :
*         延时参数个ms
*/
void Rough_DelayMs(uint16_t Time);
/*
*Parameter:Time
*					us时间(1800,000)
*Role     :
*         延时参数个us
*/
void Correct_DelayUs(uint32_t Time);
/*
*Parameter:Time
*					ms时间(1800)
*Role     :
*         延时参数个ms
*/
void Correct_DelayMs(uint16_t Time);

#endif
