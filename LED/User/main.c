#include <reg52.h>
#include "Timer.h"
#include "Led7Seg.c"
#include "main.h"
#include "port.h"

//-----------------------------------------------------------------------
//          主函数
//-----------------------------------------------------------------------
void main(void)
{
    io_led = 0; //发光二极管与数码管共用P0口,这里禁止掉发光二极管的锁存输出
    Timer0Init();
    SetClock(10, 20, 30); //设置初始时间为10点20分30秒
    EA = 1;
    while(1)
    {
        LedDisplay(g_u8LedDisplayBuffer);
        RunClock();
    }
}   









