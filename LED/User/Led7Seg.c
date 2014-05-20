#include <reg52.h>
#include "port.h"
#include "Timer.h"
#include "Led7Seg.h"


uint8 g_u8LedDisplayBuffer[8] ={0};//��ʾ������


//-----------------------------------------------------------------------
//          ��������ܵĶ����
//-----------------------------------------------------------------------

code uint8 g_u8LedDisplayCode[] =
{
    0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
    0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,
    0xbf//'-'�Ŵ���
};

#define LED_PORT P0

//-----------------------------------------------------------------------
//          ������ܶ��뺯��
//-----------------------------------------------------------------------
static void SendLedSegData(uint8 dat)
{
    LED_PORT = dat;
    io_led_seg_cs = 1;  //����������,�Ͷ�������
    io_led_seg_cs = 0;
}

//-----------------------------------------------------------------------
//          λѡͨ����
//-----------------------------------------------------------------------
static void SendLedBitData(uint8 dat)
{
    uint8 temp;
    temp = (0x01 << dat); //����Ҫѡͨ��λ�����λ��
    LED_PORT = temp;
    
    io_led_bit_cs = 1; //��λ������,��λ������
    io_led_bit_cs = 0;  
}

//-----------------------------------------------------------------------
//          ���Ķ�̬ɨ�躯��
//-----------------------------------------------------------------------
void LedDisplay(uint8 *pBuffer)
{
    static uint8 s_LedDisPos = 0;
    if(g_bSystemTime2Ms)
    {
        g_bSystemTime2Ms = 0;
        SendLedBitData(8); //���� ֻ��Ҫ����λѡ��Ϊ0~7���� �Ͷ�������֮ǰ�ص�λѡ
        if(pBuffer[s_LedDisPos] == '-') //��ʾ'-'��
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
            s_LedDisPos = 0;  //��ʾɨ������ܵ�λ��
        }
    }
}







