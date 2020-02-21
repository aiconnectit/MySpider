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
#define LEDs_NUM    sizeof (LED)/ sizeof(u8)

#define BUZZER   P06

u8 LED[] = {GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};
//char i ;
u8 MODE = 2;
u16 cnt = 0;    //timer0����
u8 n=0;
u8 nthree=0;
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);
}
void All_Init(void)
{
	//P2 = (P2 & 0x1f) | 0x80;	//��Y4C��LED��
	//P0 = 0xff;					//�ر�LED
	//P2 = (P2 & 0x1f) | 0xe0;	//��Y7C������ܣ�
	//P0 = 0xff;					//�ر������
	P2 = (P2 & 0x1f) | 0xa0;	//��Y5C
	P0 = 0x00;					//�رշ��������̵���
	P2 = P2 & 0x1f;
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

void LED_LeftToRight(u8 Pinx)
{
  
  if (Pinx == 0) 
  {
    GPIO_WritePin(GPIO_P0, LED[0] ,1);  
  }
  else if (Pinx >= LEDs_NUM) 
  {
    GPIO_WritePin(GPIO_P0, LED[LEDs_NUM-1],0);
  }
  else 
  {   
    GPIO_WritePin(GPIO_P0, LED[Pinx],1);
    Pinx--;
    GPIO_WritePin(GPIO_P0, LED[Pinx],0);    
  }
}

void LED_RightToLeft(u8 Pinx)
{
  
  if (Pinx == 7) 
  {
    GPIO_WritePin(GPIO_P0, LED[0] ,1);  
  }
  else if (Pinx <= 0) 
  {
    GPIO_WritePin(GPIO_P0, LED[0],0);
  }
  else 
  {   
    GPIO_WritePin(GPIO_P0, LED[Pinx],1);
    Pinx++;
    GPIO_WritePin(GPIO_P0, LED[Pinx],0);    
  }
}

void mode_three(u8 Pinx)//ģʽ3
{
		GPIO_WritePin(GPIO_P0 , LED[Pinx] , 1);
		GPIO_WritePin(GPIO_P0 , LED[7-Pinx] , 1);
}
void mode_four(u8 Pinx)//ģʽ4
{

		GPIO_WritePin(GPIO_P1 , LED[Pinx] , 1);
		GPIO_WritePin(GPIO_P1 , LED[7-Pinx] , 1);
		
	 
}
void timer0_int (void) interrupt TIMER0_VECTOR
{  	
	  cnt++ ;
	  if(cnt ==10000) 
		{ 
			cnt=0;
			n=1;
		}

	 
}


/******************** ������ **************************/
void main(void)
{
  u8 i=0,j=7,v=0,x=3,key_led=0;
	All_Init();
	GPIO_config();
	Timer_config();
	EA = 1;
	P2=0x80;
	while(1)
	{ 
		if(GetKeyVal_Button()==S5DOWN)
		{
			key_led++;
			if(key_led>4)
			{
				key_led=0;
			}
			
		}
		
		switch (key_led) 
    {
      case 1:
      {
				if(n==1)
				{
					n=0;
				  LED_LeftToRight(i);
					i++;
					if(i>8)
					{
						i=0;
					}
				}
			}
			break;
			
			case 2:
      {
				if(n==1)
				{
					n=0;
					
					LED_RightToLeft(j);
				  j--;	
					if(j<0)
					{
						j=7;
					}
				}
			}
			break;
			
			case 3:
      {
				if(n==1)
				{
					n=0;
					mode_three(v);
			    v++;
					if(v>4)
					{
						v=0;
					}
				}
			}
			break;
		
	    case 4:
      {
				if(n==1)
				{
					mode_four(x);
					x--;
					if(x<0)
					{
						x=3;
					}
				}
			}
			break;
	 }
 }
	
}

