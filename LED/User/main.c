#include <reg52.h>
#include "Timer.h"
#include "Led7Seg.c"
#include "main.h"
#include "port.h"

//-----------------------------------------------------------------------
//          ������
//-----------------------------------------------------------------------
void main(void)
{
    io_led = 0; //���������������ܹ���P0��,�����ֹ����������ܵ��������
    Timer0Init();
    SetClock(10, 20, 30); //���ó�ʼʱ��Ϊ10��20��30��
    EA = 1;
    while(1)
    {
        LedDisplay(g_u8LedDisplayBuffer);
        RunClock();
    }
}   









