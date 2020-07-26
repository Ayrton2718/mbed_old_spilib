/*
* SPIComm.h 更新履歴
* 2016/6/24
*   Ver1.0.0    一次完成
* 2016/10/14
*   Ver1.0.1    SSpinを追加
*/

#include "SPIComm.h"

namespace spi_lib
{
    SPIComm::SPIComm(PinName mosi, PinName miso, PinName sck)
    {
        spi = new SPI(mosi, miso, sck);
        spi->format(8, 1);
        spi->frequency(1e+6);
    }
    
    int SPIComm::spi_write(int tx_data)
    {
        return spi->write(tx_data);
    }
}
