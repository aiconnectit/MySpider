#include "main.h"
#include "gpio_ex.h"

#define MODE0_TIME 400
#define MODE1_TIME 800
#define MODE_0 0
#define MODE_1 1

bit mode0_next=0;  
bit mode1_next=0; 

unsigned int mode=0;
extern LEDs_NUM= 8;
void timer0_int (void) interrupt TIMER0_VECTOR
{  
	  static unsigned int cnt=0; 
    if (cnt++ % MODE0_TIME == 0)  mode0_next = 1;
    if (cnt++ % MODE1_TIME == 0)  mode1_next = 1 ;
    if (cnt % 60000 == 0) cnt = 0;
  
}


void main()
{
  while(1)
  {
    unsigned char i = 0;
    switch (mode) 
    {
      case MODE_0:
      {
        //做模式0要做的事  
         if (mode0_next == 1)
         {
            mode0_next = 0;
            LED_LeftToRight(i);
            if( i == LEDs_NUM) 
            {
              mode = MODE_1;
              break;
            } 
            i++;
            
         }
       }
      break;
      case MODE_1:
      {
      }
    }

  }
}