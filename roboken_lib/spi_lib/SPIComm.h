/*
* SPIComm.h 更新履歴
* 2016/6/24
*   Ver1.0.0    一次完成
* 2016/10/14
*   Ver1.0.1    SSpinを追加
*/

/*
 * > mode | POL PHA
 * > -----+--------
 * >   0  |  + Latch
 * >   1  |  + Shift
 * >   2  |  - Latch
 * >   3  |  - Shift
*/

#ifndef SPI_COMM_H_
#define SPI_COMM_H_

#include "mbed.h"

namespace spi_lib
{ 
    class SPIComm
    {
    private:
        SPI *spi;
    
    public:
        SPIComm(PinName mosi, PinName miso, PinName sck);
        int spi_write(int tx_data);
    };
}

#endif
