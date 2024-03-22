#include "scheduler.h"
#include "dcu.h"
#include "gps.h"
#include "serial_device.h"

int main() {
    EAR::Scheduler scheduler;
    GPS gps[2] = {GPS {"1"}, GPS {"2"}};
    DCU dcu {"dcu"};
    SerialDevice serdev[2];
    
    gps[0].setIODevice(&serdev[0]);
    gps[1].setIODevice(&serdev[1]);

    gps[0].open();
    gps[1].open();
    dcu.open();
    
    dcu.subscribe(&gps[0], 0U);
    dcu.subscribe(&gps[1], 0U);
    
    if (!scheduler.add(&gps[0], 400000U) ||
	!scheduler.add(&gps[1], 600000U) ||
	!scheduler.add(&dcu, 100000U)) {
	return -1;
    }

    if (!scheduler.start()) { return -1; }
    spdlog::info("scheduler running");

    std::this_thread::sleep_for(std::chrono::milliseconds(1300));

    if (!scheduler.stop()) { return -1; }
    spdlog::info("schedulers terminated");

    gps[0].close();
    gps[1].close();
    dcu.close();

    
    return 0;
}
