#include	"config.h"
#include	"GPIO.h"
#include	"delay.h"
#include  "timer.h"
#include  "key.h"

#define LED0_Pin GPIO_Pin_0
#define LED1_Pin GPIO_Pin_1
#define LED2_Pin GPIO_Pin_2
#define LED3_Pin GPIO_Pin_3
#define LED4_Pin GPIO_Pin_4
#define LED5_Pin GPIO_Pin_5
#define LED6_Pin GPIO_Pin_6

void All_Init(void)
{
	
	P0 = 0xff;					//关闭数码管
	P2 = (P2 & 0x1f) | 0xa0;	//打开Y5C
	P0 = 0x00;					//关闭蜂鸣器、继电器
	P2 = P2 & 0x1f;
}

void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);
}
/*
void TWO_init(u8 pinx)
{
	
	
}
*/
/******************** 主函数 **************************/
void main(void)
{
  u16 key_led=1;
	All_Init();
	GPIO_config();
	while(1)
	{
		
		P2=0x80;
		if(GetKeyVal_Button()==S5DOWN)
		{
			key_led++;
			if(key_led>3)
			{
				key_led=1;
			}
		}
		switch(key_led) 
    {
      case 1:
      {
				P0=0xff;
			  GPIO_WritePin(GPIO_P0, GPIO_Pin_0 ,0); 
		    delay_ms(200);
				GPIO_WritePin(GPIO_P0, GPIO_Pin_0 ,1);
				
			}
			break;
			
			case 2:
      {
			  P0=0xff;
				GPIO_WritePin(GPIO_P0, GPIO_Pin_0 ,0); 
			  delay_ms(400);
				GPIO_WritePin(GPIO_P0, GPIO_Pin_0 ,1); 
			}
			break;
			
			case 3:
      {
				P0=0xff;
				GPIO_WritePin(GPIO_P0, GPIO_Pin_0 ,0); 
			  delay_ms(800);
				GPIO_WritePin(GPIO_P0, GPIO_Pin_0 ,1); 
			}
			break;
		
	 }

 }
	
}

