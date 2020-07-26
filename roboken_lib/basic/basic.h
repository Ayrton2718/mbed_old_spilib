#ifndef ROBOKEN_LIB_BASIC_BASIC_H
#define ROBOKEN_LIB_BASIC_BASIC_H

#include "mbed.h"

namespace roboken_basic
{

static mbed::DigitalOut led1(LED1);
static mbed::DigitalOut led2(LED2);
static mbed::DigitalOut led3(LED3);
static mbed::DigitalOut led4(LED4);

// static DigitalOut safety(p8);
static DigitalOut safety(PC_0);


void safetyHigh(void);
void safetyLow(void);

unsigned char make8(unsigned int data, unsigned char num);
unsigned short make16(unsigned char data2, unsigned char data1);
unsigned int make32(unsigned char data4, unsigned char data3, unsigned char data2, unsigned char data1);

void wait_ms(int ms);

}

#endif /* ROBOKEN_LIB_BASIC_BASIC_H */