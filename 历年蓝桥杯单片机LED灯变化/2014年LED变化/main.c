#include	"config.h"
#include	"GPIO.h"
#include	"delay.h"
#include  "timer.h"
#include  "key.h"

#define BUZZER   P06


#define LED0_Pin GPIO_Pin_0
#define LED1_Pin GPIO_Pin_1
#define LED2_Pin GPIO_Pin_2
#define LED3_Pin GPIO_Pin_3
#define LED4_Pin GPIO_Pin_4
#define LED5_Pin GPIO_Pin_5
#define LED6_Pin GPIO_Pin_6

u16 cnt = 0;    //timer0����
bit n=0;
bit K=0;
bit d=0;

void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);
}

void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_8BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;//DISABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 5;		//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2
}



void timer0_int (void) interrupt TIMER0_VECTOR
{  	
    cnt++ ;
	  if(cnt ==200) 
		{ 
			cnt=0;
			n=1;
			
		}else if(cnt ==400)
		{
			cnt=0;
			K=1;
		}else if(cnt ==800)
		{
			cnt=0;
			d=1;
		}
		
}


/******************** ������ **************************/
void main(void)
{
  u16 key_led=0;
	GPIO_config();
	Timer_config();
	EA = 1;
	while(1)
	{
		P2=0x80;
		if(GetKeyVal_Button()==S5DOWN)
		{
			key_led++;
			if(key_led>5)
			{
				key_led=0;
			}
		switch (key_led) 
    {
      case 1:
      {
				if(n==1)
				{
					n=0;
					GPIO_WritePin(GPIO_P0, GPIO_Pin_0 ,1); 
				}
			}
			break;
			
			case 2:
      {
				if(K==1)
				{
					K=0;
				  GPIO_WritePin(GPIO_P0, GPIO_Pin_1 ,1); 
				}
			}
			break;
			
			case 3:
      {
				if(d==1)
				{
					d=0;
				  GPIO_WritePin(GPIO_P0, GPIO_Pin_2 ,1); 
			
				}
			}
			break;
		
	 }
	
  }
 }
	
}

