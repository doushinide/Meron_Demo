#ifndef _TIMER_H_
#define _TIMER_H_

#include "port.h"

extern void Timer0Init(void);
extern bit g_bSystemTime2Ms;
//extern bit g_bTime1S;  //Ҫô��extern Ҫô���ж�ȥ��  .c���Ѿ��������
extern void SetClock(uint8 nHour, uint8 nMinute, uint8 nSecond);
extern void RunClock(void);


#endif