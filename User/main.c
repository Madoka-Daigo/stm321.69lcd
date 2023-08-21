#include "main.h" 
#include "pic.h"

int main()
{	
	uint8_t counter=1,k=1;
	WRCACE_InitTypedef WRCACE_InitStruct;
	WRCACE_InitStruct.Adaptive_Brightness_Goal=0x10;
	WRCACE_InitStruct.Color_Enhancement_Cmd=1;
	WRCACE_InitStruct.Color_Enhancement_Extent=11;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	My_Usart_Init(115200);//可以换成自己的usart相关函数
	ST7789V_LcdInit();
	ST7789V_AdaptiveBrightnessColorEnhancementInit(&WRCACE_InitStruct);
	printf("ST7789V Ready!\n");
	ST7789V_FillLcdScreen(0,0,LCD_W,LCD_H,WHITE,USE_HORIZONTAL);
	CST816T_Init();
	printf("CST816T Ready!\n");
	while(1)
	{
		
		ST7789V_LcdShowChinese(30,175,"大古大帅哥",LGRAYBLUE,WHITE,32,0,USE_HORIZONTAL);
        ST7789V_LcdShowChinese(30,220,"三连＋关注",LBBLUE,WHITE,32,0,USE_HORIZONTAL);

        if((State==0x05)&&((0<X_Axis<=200)&&(130<=Y_Axis<=250)))
		{
			if(counter<3)
			{
				counter++;
			}
		
			k=1;
		}
		if((State==0x05)&&((0<X_Axis<=200)&&(0<Y_Axis<=100)))
		{
			if(counter>0)
			{
				counter--;
			}
			
			k=1;
		}
		if(k==1)
		{
			switch(counter)
			{
				case 1:
					ST7789V_FillLcdScreen(0,0,200,170,WHITE,USE_HORIZONTAL);
					ST7789V_LcdShowPicture(40,20,150,150,gImage_1111,USE_HORIZONTAL);
					CST816T_ClrBaseDatas();
				k=0;
				break;
				case 2:
					ST7789V_FillLcdScreen(0,0,200,170,WHITE,USE_HORIZONTAL);
                    ST7789V_LcdShowPicture(70,30,100,100,gImage_3333,USE_HORIZONTAL);
					CST816T_ClrBaseDatas();
				k=0;
				break;
				case 3:
					ST7789V_FillLcdScreen(0,0,200,170,WHITE,USE_HORIZONTAL);
                    ST7789V_LcdShowPicture(40,20,150,140,gImage_2222,USE_HORIZONTAL);
					CST816T_ClrBaseDatas();
				k=0;
				break;
			}
		}
	}
}
