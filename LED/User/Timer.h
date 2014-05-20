#ifndef _TIMER_H_
#define _TIMER_H_

#include "port.h"

extern void Timer0Init(void);
extern bit g_bSystemTime2Ms;
//extern bit g_bTime1S;  //要么加extern 要么整行都去掉  .c中已经定义过了
extern void SetClock(uint8 nHour, uint8 nMinute, uint8 nSecond);
extern void RunClock(void);


#endif