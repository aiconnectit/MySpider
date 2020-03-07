#include "main.h"
#include "gpio_ex.h"
#include "key.h"
#define MODE0_TIME 400
#define MODE1_TIME 800
#define MODE_0 0
#define MODE_1 1

bit mode0_next=0;  
bit mode1_next=0; 

unsigned int mode=0;

extern LEDs_NUM= 8;

void timer0_int(void) interrupt TIMER0_VECTOR
{  
	  static unsigned int cnt=0; 
    if (cnt++ % MODE0_TIME == 0)  mode0_next = 1;
    if (cnt++ % MODE1_TIME == 0)  mode1_next = 1 ;
    if (cnt % 60000 == 0) cnt = 0;
  
}

void main()
{

	P2=0x80;
  while(1)
  {
     if(getkey()==5)
		 {
			 GPIO_WritePin(GPIO_P0,GPIO_Pin_1,1);
		 }

   }
}