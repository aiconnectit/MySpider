#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "GPIO.h"


//LED控制
#define ON     1
#define OFF    0
#define LED_PORT  P0
#define LED0_Pin GPIO_Pin_0
#define LED1_Pin GPIO_Pin_1
#define LED2_Pin GPIO_Pin_2
#define LED3_Pin GPIO_Pin_3
#define LED4_Pin GPIO_Pin_4
#define LED5_Pin GPIO_Pin_5
#define LED6_Pin GPIO_Pin_6
#define LED7_Pin GPIO_Pin_7


void LED_On(u8 led_port,u8 led_pin );
void LED_Off(u8 led_port,u8 led_pin);
void LED_Toggle(u8 led_port,u8 led_pin);
void LED_LeftToRight(u8 Pinx);

#endif 
