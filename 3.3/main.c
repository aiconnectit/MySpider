#include	"config.h"
#include	"GPIO.h"
#include	"delay.h"
#include  "timer.h"

#define  MODE1   0x01   //模式1标志
#define  MODE2   0x02   //模式2标志
#define  MODE3   0x03   //模式3标志
#define  MODE4   0x04   //模式4标志

#define  MS1   1000      //模式1间隔时间ms
#define  MS2   500      //模式2间隔时间ms
#define  MS3   200      //模式3间隔时间ms
#define  MS4   800      //模式4间隔时间ms

#define BUZZER_OPEN  500     //蜂鸣器响应时间ms
#define BUZZER_CLOSE  1000    //蜂鸣器停止时间ms

#define BUZZER   P25

u8 LED[] = {GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};
char i ;
u8 MODE = 2;
u16 n = 0;    //timer0计数

void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);
}

void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义
	TIM_InitStructure.TIM_Mode      = TIM_8BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//指定中断优先级, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;//DISABLE;				//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 5;		//初值,
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2
}

void mode_one()//模式1
{
	P1 = 0xff;
	delay_ms(MS1/2);
	for(i = 0 ; i < 8 ; i ++ )
	{
		GPIO_WritePin(GPIO_P1 , LED[i] , LOW);
		delay_ms(MS1/2);
	}
}

void mode_two()//模式2
{
	P1 = 0xff;
	delay_ms(MS2/2);
	for(i = 7 ; i >= 0 ; i -- )
	{
		GPIO_WritePin(GPIO_P1 , LED[i] , LOW);
		delay_ms(MS2/2);
	}
}

void mode_three()//模式3
{
	P1 = 0xff;
	delay_ms(MS3/2);
	for(i = 0 ; i < 4 ; i ++ )
	{
		GPIO_WritePin(GPIO_P1 , LED[i] , LOW);
		GPIO_WritePin(GPIO_P1 , LED[7-i] , LOW);
		delay_ms(MS3/2);
	}
}

void mode_four()//模式4
{
	P1 = 0xff;
	delay_ms(MS4/2);
	for(i = 3 ; i >= 0 ; i -- )
	 {
		GPIO_WritePin(GPIO_P1 , LED[i] , LOW);
		GPIO_WritePin(GPIO_P1 , LED[7-i] , LOW);
		delay_ms(MS4/2);
	 }
}

void timer0_int (void) interrupt TIMER0_VECTOR
{  
	  n++ ;
	  if( n <= 4*BUZZER_CLOSE)  BUZZER = 0;
	  else if(n <= (4*BUZZER_OPEN + 4*BUZZER_CLOSE)) BUZZER = 1;
	  else  n = 0;
}


/******************** 主函数 **************************/
void main(void)
{
	GPIO_config();
	Timer_config();
	EA = 1;
	while(1)
	{
		//if(MODE == MODE1) mode_one();
		//if(MODE == MODE2) mode_two();
		//if(MODE == MODE3) mode_three();	
		//if(MODE == MODE4) mode_four();	
		mode_one();
		mode_two();
		mode_three();
    mode_four();			
	}
}




