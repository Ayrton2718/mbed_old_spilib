#include "basic.h"

namespace roboken_basic
{

//---------------- データ分割 -------------------//
    // 8bitに分解
unsigned char make8(unsigned int data, unsigned char num)
{
    return (unsigned char)( (data >> (num * 8)) & 0xff );
}

// 8bitデータから16bitデータを構成
unsigned short make16(unsigned char data2, unsigned char data1)
{
    unsigned short data = 0;

    data |= (unsigned short)data1;
    data |= (unsigned short)data2 << 8;

    return data;
}

// 8bitデータから32bitデータを構成
unsigned int make32(unsigned char data4, unsigned char data3, unsigned char data2, unsigned char data1)
{
    unsigned int data = 0;

    data |= (unsigned int)data1;
    data |= (unsigned int)data2 << 8;
    data |= (unsigned int)data3 << 16;
    data |= (unsigned int)data4 << 24;

    return  data;
}

//-------- セーフティピン ----------//
// セーフティピンLOW
void safetyLow(void)
{
    // DigitalOut safety(p8, 0);

    DigitalOut safety(PC_7, 0);
}

// セーフティピンHIGH
void safetyHigh(void)
{
    // DigitalOut safety(p8, 1);

    DigitalOut safety(PC_7, 1);
}

void wait_ms(int ms)
{
    ThisThread::sleep_for((Kernel::Clock::duration_u32)ms);
}

}