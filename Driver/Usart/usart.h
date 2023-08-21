#ifndef _usart_H
#define _usart_H

#include <stm32f10x.h>

/**************************************/
#define USART_ON

#ifdef USART_ON

/*
*Baud_Rate:Baud_Rate,
*					波特率
*Role     :初始化USART
*/
void My_Usart_Init(uint32_t Baud_Rate);
/*
*Parameter:USARTx,
*					选择串口
*Parameter:Buffer,
*					数据缓冲区
*Parameter:Length,
*					数据长度
*Role     :串口发送多个字节
*/
void Usart_Send_Bytes(USART_TypeDef* USARTx,uint8_t* Buffer,uint16_t Length);
/*
*Parameter:USARTx,
*					选择串口
*Parameter:Buffer,
*					数据缓冲区
*Role     :串口接收多个字节
*Return   ：返回数据长度（最大65535字节）
*/
uint16_t Usart_Receive_Bytes(USART_TypeDef* USARTx,uint8_t*Buffer,uint16_t Max_Length);

#define USART_IT_ON    DISABLE//ENABLE

#if Usart_IT_ON==ENABLE

#define USART1_REC_LEN		200  	//定义最大接收字节数 200
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         		//接收状态标记

/*
*Role     :中断开启
*/
void Usart_ITON(void);

#endif
/*USART结束*/
#endif

#endif
