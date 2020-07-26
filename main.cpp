#include "mbed.h"
#include "rtos.h"
#include "roboken_lib/spi_lib/SPILib.h"

/*
NUCLEO　注意事項
saftyピン変更
SPI各種pinの変更
以上
 */

SPILib g_spi(1, 0, 0);


// Spawns a thread to run blink for 5 seconds
int main() {
    roboken_basic::wait_ms(100);

    g_spi.driverInit(SLOT1, 1);
}