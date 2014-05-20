#include <reg52.h>
#include "Timer.h"
#include "port.h"
#include "main.h"
#include "Led7Seg.h"

bit g_bSystemTime2Ms = 0;     //ʱ��2msʱ����Ϣ
bit g_bTime1S = 0; //ʱ��1sʱ����Ϣ

static uint16 s_u16ClockTickCount = 0; //��2msʱ����м���

//-----------------------------------------------------------------------
//          ��ʱ��0��ʼ������
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
//          ��ʱ��0�жϺ���
//-----------------------------------------------------------------------
void Time0Isr(void)interrupt 1
{
    TH0 = 0xf8; //��ʱ�����¸���ֵ
    TL0 = 0xcc;
    g_bSystemTime2Ms = 1; //2MSʱ���־λ ��λ
    
    if(++s_u16ClockTickCount == 500)
    {
        s_u16ClockTickCount = 0;
        g_bTime1S = 1;
    }
}

//-----------------------------------------------------------------------
//          ˢ���������ʾ����������
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
                            if(++g_u8LedDisplayBuffer[1] == 4) // 24����
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
//          ʱ�ӳ�ʼֵ���ú���
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




