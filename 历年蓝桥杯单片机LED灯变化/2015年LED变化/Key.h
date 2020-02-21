#ifndef __KEY_H__
#define __KEY_H__

#include	"config.h"
#include "DataType.h"

#define S4	P33
#define S5	P32
#define S6	P31
#define S7	P30

#define NOKEY	0
#define S7DOWN	7
#define S6DOWN	6
#define S5DOWN	5
#define S4DOWN	4


#define S8DOWN	8
#define S9DOWN	9
#define S10DOWN	10
#define S11DOWN	11
#define S12DOWN	12
#define S13DOWN	13
#define S14DOWN	14
#define S15DOWN	15
#define S16DOWN	16
#define S17DOWN	17
#define S18DOWN	18
#define S19DOWN	19

#define S6HOLD	20
extern uChar8 GetKeyVal_Button(void);	//独立式按键读取键值函数
extern uChar8 GetKeyVal_Keyboard(void);	//行列式按键读取键值函数

#endif