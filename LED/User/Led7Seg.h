#ifndef _LED7SEG_H_
#define _LED7SEG_H_

#include "port.h"

extern uint8 g_u8LedDisplayBuffer[];//ÏÔÊ¾»º³åÇø

static void SendLedSegData(uint8 dat);
static void SendLedBitData(uint8 dat);

extern void LedDisplay(uint8 *pBuffer);


#endif