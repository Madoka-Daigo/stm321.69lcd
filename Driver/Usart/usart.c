#include "usart.h"

#ifdef USART_ON 

#include "stdio.h"

void My_Usart_Init(uint32_t Baud_Rate)
{
	 //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	//USART配置
	USART_InitTypeDef USART_InitStructure;
	//中断通道设置
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//串口使能（其它USART在APB1）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

	//USART1 初始化设置
	USART_InitStructure.USART_BaudRate = Baud_Rate;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);//清除中断标志
	USART_ClearFlag(USART1,USART_FLAG_RXNE);

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

void Usart_Send_Bytes(USART_TypeDef* USARTx,uint8_t*Buffer,uint16_t Length)
{
	uint16_t i;//最大接收字数位65535
	for(i=0;i<Length;i++)
	{
		USART_SendData(USARTx,*(Buffer+i));         //向串口1发送数据
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);//等待发送结束
		USART_ClearFlag(USARTx, USART_FLAG_TC);
	}
}
uint16_t Usart_Receive_Bytes(USART_TypeDef* USARTx,uint8_t*Buffer,uint16_t Max_Length)
{
	uint16_t Counter=0xffff,
	i=0;//最大接收字数位65535
	(Max_Length!=0)?(Max_Length=Max_Length):(Max_Length=65535);
	while((Counter--)&&(i!=Max_Length))
	{
		if(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)==SET)
		{
			*(Buffer+i)=(uint8_t)USARTx->DR;//USART_ReceiveData(USARTx);
			USART_ClearFlag(USARTx,USART_FLAG_RXNE);
			Counter=0xffff;
			i++;
		}
	}
	return i;
}

/*使用printf函数时使用*/
int fputc(int ch,FILE *p) 
{
	USART_SendData(USART1//选择输出串口
											,(u8)ch);
	while(USART_GetFlagStatus(USART1//选择输出串口
											,USART_FLAG_TXE)==RESET); 
	return ch;
}

#if USART_IT_ON==ENABLE

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记

void USART_ITON(void)
{
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
}

void USART1_IRQHandler(void)
{
	u8 r;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		r =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		if((USART1_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART1_RX_STA&0x4000)//接收到了0x0d
			{
				if(r!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
				else USART1_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(r==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=r;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	}
}

#endif
/*USART结束*/
#endif
