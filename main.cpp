#include "mbed.h"
#include "rtos.h"

Thread thread;
DigitalOut led1(LED2);

// USBSerial serial;

#define STOP_FLAG 1

// Blink function toggles the led in a long running loop
void blink(DigitalOut *led) {
    while (!ThisThread::flags_wait_any_for(STOP_FLAG, (Kernel::Clock::duration_u32)500)) {
        *led = !*led;
    }
}

// Spawns a thread to run blink for 5 seconds
int main() {
    thread.start(callback(blink, &led1));
    ThisThread::sleep_for((Kernel::Clock::duration_u32)10000);
    thread.flags_set(STOP_FLAG);
    thread.join();
}