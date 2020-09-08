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

    printf("start\n");

    // g_spi.setInitMode(SLOT3, MOT);
    // g_spi.setMotorDuty(SLOT3, 0x80);
    // g_spi.setInitFunwariH(SLOT3, 3);
    // g_spi.setInitFunwariL(SLOT3, 3);
    // while(true)
    // {
    //     int ans = g_spi.driverInit(SLOT3);
    //     printf("%d", ans);
    //     if(ans != 1)
    //     {
    //         break;
    //     }

    //     roboken_basic::wait_ms(10);
    // }
    // roboken_basic::wait_ms(100);

    // printf("success init\n");

    // roboken_basic::safetyLow();

    // while(true)
    // {
    //     g_spi.driverSendMD(SLOT1, 0xA0);
    //     roboken_basic::wait_ms(100);
    // }
}