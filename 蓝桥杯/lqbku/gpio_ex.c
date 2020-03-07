
#include "gpio_ex.h"


u8 GPIO_WritePin(u8 GPIO , u8 Pinx , bit Level)
 { 
	 if(GPIO > GPIO_P5)				return 1;	
	 if(Pinx > GPIO_Pin_All)	return 2;	
	 if(GPIO == GPIO_P0)
	  {
	   if(Level)
		  P0 &= (~Pinx);
	   else
	    P0 |= Pinx;
    }
		return 0;
 }

 u8 GPIO_ReadPin(u8 GPIO , u8 Pinx )
 { 
	 if(GPIO > GPIO_P5)				return 3;	
	 if(Pinx > GPIO_Pin_All)	return 2;	
	  if(GPIO == GPIO_P0)
	  {
      if ( P0 & Pinx != 0)
		  return 1;
	    else
	    return 0;
    }
		
		return 0;
 }

u8 GPIO_TogglePin(u8 GPIO , u8 Pinx )
 { 
	 if(GPIO > GPIO_P5)				return 1;	
	 if(Pinx > GPIO_Pin_All)	return 2;	
	 if(GPIO == GPIO_P0)      P0 ^= Pinx;
	 
	 return 0;
 }
 

