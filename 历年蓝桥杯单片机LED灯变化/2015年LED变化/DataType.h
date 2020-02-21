//此文件用于定义新数据类型，如系统状态枚举等
#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#define uChar8 unsigned char
#define uInt16 unsigned int
//以下是界面号
#define HX_V	0	//回显电压
#define HX_F	1	//回显频率
#define HX_T	2	//回显温度


typedef enum{NoKey, KeyDown, KeyHold, KeyUp} KeyState_T;
typedef enum{GetVStatus, GetFStatus, GetTStatus, ReviewStatus, SetStatus} SystemState_T;

#endif