#include "Key.h"


code uChar8 RowScanVal[4] = {0xfe, 0xfd, 0xfb, 0xf7};	//键盘逐行扫描值
/**********************************************************
函数名称：GetKeyVal_Button
函数功能：读取独立按键，仅采集按下动作，返回按键字面值
入口参数：无
出口参数：KeyVal按下键的字面值
备注：
**********************************************************/
uChar8 GetKeyVal_Button(void)	//独立式按键读取键值函数
{
	static uChar8 k4_old = 0x0f;		//上次按键电平值
	static KeyState_T S6State = NoKey;	//S6微状态
	static uChar8 S6_LOW_cnt = 0;		//S6低电平计时器
	uChar8 k4_now, tmp, KeyVal;
	
	P3 = 0xff
	k4_now = P3 & 0x0f;		//读取按键值（低四位）
	
	tmp = k4_old ^ k4_now;	//异或求变化，有变化的位为1
	if(tmp)					//若按键有新动作，不支持组合键，仅对按键按下有响应
	{
		S6_LOW_cnt = 0;		
		switch(tmp)
		{
			case 0x01:	if(S7)
							KeyVal = NOKEY;		//S7松开
						else
							KeyVal = S7DOWN;	//S7按下
						break;
			case 0x02:	if(S6)
							KeyVal = NOKEY;		//S6松开
						else
						{
							KeyVal = S6DOWN;	//S6按下
							S6State = KeyDown;
						}
						break;
			case 0x04:	if(S5)
							KeyVal = NOKEY;		//S5松开
						else
							KeyVal = S5DOWN;	//S5按下
						break;
			case 0x08:	if(S4)
							KeyVal = NOKEY;		//S4松开
						else
							KeyVal = S4DOWN;	//S4按下
						break;
			default:	KeyVal = NOKEY; 
						break;
		}
	}
	else		//无变化，需要考虑S6长按
	{
		if(!S6)
		{
			if(S6State == KeyDown)
			{
				if(++ S6_LOW_cnt == 80)	//0.8秒
				{
					S6State = KeyHold;
					KeyVal = S6HOLD;
				}
				else
					KeyVal = NOKEY;		//不到0.8秒
			}
			else if(S6State == KeyHold)	//超过0.8秒
				KeyVal = S6HOLD;
		}
		KeyVal = NOKEY;
	}	
	k4_old = k4_now;	//备份本次按键电平值
	return KeyVal;
}

/**********************************************************
函数名称：GetKeyVal_Keyboard
函数功能：读取当前行的按键电平，对比上次该行的电平值
仅采集按下动作，返回按键字面值，并扫描下一行按键
入口参数：无
出口参数：KeyVal按下键的字面值
备注：不支持组合键
**********************************************************/
uChar8 GetKeyVal_Keyboard(void)	//行列式按键读取键值函数
{
	static uChar8 column_old[4] = {0xf0, 0xf0, 0xf0, 0xf0};	//备份的上次读取列的电平值，共4行。
														//函数每执行一次，备份一行即更新一个元素
	static uChar8 row_i = 0;	//当前行索引
	
	uChar8 column_now, tmp, col, colrow, KeyVal;
	
	col = 0x80;
	column_now = P3 & 0xf0;		//读取当前行对应的列电平值，高四位有效
	
	tmp = column_now ^ column_old[row_i];	//异或求变化，有变化的位为1
	
	if(tmp)			//有变化
	{
		while(tmp <<= 1)
			col >>= 1;		//确定列号
		if(col & column_now)
			KeyVal = NOKEY;	//松开
		else
		{
			colrow = col | (1 << row_i);	//组成行列值
			switch(colrow)
			{
				case 0x88:	KeyVal = S4DOWN; break;
				case 0x84:	KeyVal = S5DOWN; break;
				case 0x82:	KeyVal = S6DOWN; break;
				case 0x81:	KeyVal = S7DOWN; break;
				case 0x48:	KeyVal = S8DOWN; break;
				case 0x44:	KeyVal = S9DOWN; break;
				case 0x42:	KeyVal = S10DOWN; break;
				case 0x41:	KeyVal = S11DOWN; break;
				case 0x28:	KeyVal = S12DOWN; break;
				case 0x24:	KeyVal = S13DOWN; break;
				case 0x22:	KeyVal = S14DOWN; break;
				case 0x21:	KeyVal = S15DOWN; break;
				case 0x18:	KeyVal = S16DOWN; break;
				case 0x14:	KeyVal = S17DOWN; break;
				case 0x12:	KeyVal = S18DOWN; break;
				case 0x11:	KeyVal = S19DOWN; break;
				default: KeyVal = NOKEY; break;
			}
		}
		
	}
	else			//无变化
	{
		KeyVal = NOKEY;
	}
	column_old[row_i++] = column_now;	//备份当前行扫描值
	P3 = RowScanVal[row_i];				//扫描下一行
	return KeyVal;
}