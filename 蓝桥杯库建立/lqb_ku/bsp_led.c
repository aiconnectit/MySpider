 //#include< > 到编译器的安装路径下的库里寻找标准库文件。如#include<stdio.h>引用的就是C:\Keil\c51\INC\stdio.h这个头文件
#include "bsp_led.h"   // #include“ ” 先到当前工程目录下寻找开发者自定义的文件，如果没有再到IDE配置的自定义路径下寻找文件。
#include "gpio_ex.h" 
 //LED_On(LED_PORT , LED0_Pin , ON);
//LED_On(LED_PORT , LED1_Pin , ON);
//上述两条语句执行完，LED0亮。
#define LEDs_NUM sizeof(LED)/ sizeof(LED[0])
extern u8 code LED[] = {LED0_Pin, LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin, LED5_Pin, LED6_Pin, LED7_Pin};

void LED_On(u8 led_port,u8 led_pin )
{
  GPIO_WritePin(led_port ,led_pin , ON);
}

void LED_Off(u8 led_port,u8 led_pin)
{
  GPIO_WritePin(led_port ,led_pin , OFF);
}

void LED_Toggle(u8 led_port,u8 led_pin)
{
  GPIO_TogglePin(led_port , led_pin );
}

void LED_LeftToRight(u8 Pinx)
{
  
  if (Pinx == 0) //仅点亮Left的LED
  {
    LED_Toggle(LED_PORT, LED[0]);  
  }
  else if (Pinx >= LEDs_NUM) //仅熄灭Right的LED
  {
    LED_Toggle(LED_PORT, LED[LEDs_NUM-1]);
  }
  else //先点亮右边的LED，再熄灭左边的
  {   
    LED_Toggle(LED_PORT, LED[Pinx]);
    Pinx--;
    LED_Toggle(LED_PORT, LED[Pinx]);    
  }
}





