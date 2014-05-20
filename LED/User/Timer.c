#include <reg52.h>
#include "Timer.h"
#include "port.h"
#include "main.h"
#include "Led7Seg.h"

bit g_bSystemTime2Ms = 0;     //时钟2ms时标消息
bit g_bTime1S = 0; //时钟1s时标消息

static uint16 s_u16ClockTickCount = 0; //对2ms时标进行计数

//-----------------------------------------------------------------------
//          定时器0初始化函数
//-----------------------------------------------------------------------
void Timer0Init(void)
{
    TMOD &= 0xf0;
    TMOD |= 0x01;
    TH0 = 0xf8;
    TL0 = 0xcc;
    TR0 = 1;
    ET0 = 1;
}

//-----------------------------------------------------------------------
//          定时器0中断函数
//-----------------------------------------------------------------------
void Time0Isr(void)interrupt 1
{
    TH0 = 0xf8; //定时器重新赋初值
    TL0 = 0xcc;
    g_bSystemTime2Ms = 1; //2MS时标标志位 置位
    
    if(++s_u16ClockTickCount == 500)
    {
        s_u16ClockTickCount = 0;
        g_bTime1S = 1;
    }
}

//-----------------------------------------------------------------------
//          刷新数码管显示缓冲区函数
//-----------------------------------------------------------------------
void RunClock(void)
{
    if(g_bTime1S )
    {
        g_bTime1S = 0;
        if(++g_u8LedDisplayBuffer[7] == 10)   //seconds
        {
            g_u8LedDisplayBuffer[7] = 0;
            if(++g_u8LedDisplayBuffer[6] == 6) 
            {
                g_u8LedDisplayBuffer[6] = 0;
                if(++g_u8LedDisplayBuffer[4] == 10) //min
                {
                    g_u8LedDisplayBuffer[4] = 0;
                    if(++g_u8LedDisplayBuffer[3] == 6)
                    {
                        g_u8LedDisplayBuffer[3] = 0;
                        if( g_u8LedDisplayBuffer[0]<2) //hour
                        {
                            if(++g_u8LedDisplayBuffer[1]==10)
                            {
                                g_u8LedDisplayBuffer[1] = 0;
                                g_u8LedDisplayBuffer[0]++;
                            }
                        }
                        else
                        {
                            if(++g_u8LedDisplayBuffer[1] == 4) // 24清零
                            {
                                g_u8LedDisplayBuffer[1]=0;
                                g_u8LedDisplayBuffer[0]=0;
                            }
                        } //hour high
                    } //hour low
                }
            }
        }
    }
}

//-----------------------------------------------------------------------
//          时钟初始值设置函数
//-----------------------------------------------------------------------
void SetClock(uint8 nHour, uint8 nMinute, uint8 nSecond)
{                       
    g_u8LedDisplayBuffer[0] = nHour/10;
    g_u8LedDisplayBuffer[1] = nHour%10;
    g_u8LedDisplayBuffer[2] = '-' ;
    g_u8LedDisplayBuffer[3] = nMinute/10;
    g_u8LedDisplayBuffer[4] = nMinute%10;
    g_u8LedDisplayBuffer[5] = '-' ;
    g_u8LedDisplayBuffer[6] = nSecond/10;
    g_u8LedDisplayBuffer[7] = nSecond%10;
}




