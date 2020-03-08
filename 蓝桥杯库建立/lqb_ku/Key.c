#include "Key.h"

u8 getkey(void)	
{
	u8 key_old=0x0f;		
	u8 key_now, tmp, keyval;
	P3 = ke_of;
	key_now=P3&0x0f;		
	tmp=key_old^key_now;	
		switch(tmp)
		{
			case 0x01:	keyval = s7key;	
				break;
			
			case 0x02:	keyval = s6key;	
				break;
			
			case 0x04:	keyval = s5key;
				 break;
			
			case 0x08:	keyval = s4key;	
		  	 break;
		}
		key_old = key_now;	
	return keyval;
}
	

