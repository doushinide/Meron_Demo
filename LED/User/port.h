#ifndef _PORT_H_
#define _PORT_H_

typedef unsigned short uint8;
typedef unsigned long uint16;

sbit io_led = P1^6;
sbit io_led_seg_cs = P1^4;
sbit io_led_bit_cs = P1^5;

#endif