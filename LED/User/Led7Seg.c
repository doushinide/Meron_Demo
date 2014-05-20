#include <reg52.h>
#include "port.h"
#include "Timer.h"
#include "Led7Seg.h"


uint8 g_u8LedDisplayBuffer[8] ={0};//显示缓冲区


//-----------------------------------------------------------------------
//          共阳数码管的段码表
//-----------------------------------------------------------------------

code uint8 g_u8LedDisplayCode[] =
{
    0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
    0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,
    0xbf//'-'号代码
};

#define LED_PORT P0

//-----------------------------------------------------------------------
//          送数码管段码函数
//-----------------------------------------------------------------------
static void SendLedSegData(uint8 dat)
{
    LED_PORT = dat;
    io_led_seg_cs = 1;  //开段码锁存,送段码数据
    io_led_seg_cs = 0;
}

//-----------------------------------------------------------------------
//          位选通函数
//-----------------------------------------------------------------------
static void SendLedBitData(uint8 dat)
{
    uint8 temp;
    temp = (0x01 << dat); //根据要选通的位计算出位码
    LED_PORT = temp;
    
    io_led_bit_cs = 1; //开位码锁存,送位码数据
    io_led_bit_cs = 0;  
}

//-----------------------------------------------------------------------
//          核心动态扫描函数
//-----------------------------------------------------------------------
void LedDisplay(uint8 *pBuffer)
{
    static uint8 s_LedDisPos = 0;
    if(g_bSystemTime2Ms)
    {
        g_bSystemTime2Ms = 0;
        SendLedBitData(8); //消隐 只需要设置位选不为0~7即可 送段码数据之前关掉位选
        if(pBuffer[s_LedDisPos] == '-') //显示'-'号
        {
            SendLedSegData(g_u8LedDisplayCode[16]);
        }
        else
        {
            SendLedSegData(g_u8LedDisplayCode[pBuffer[s_LedDisPos]]);
        }
        SendLedBitData(s_LedDisPos);
        
        if(++s_LedDisPos > 7)
        {
            s_LedDisPos = 0;  //表示扫描数码管的位置
        }
    }
}







