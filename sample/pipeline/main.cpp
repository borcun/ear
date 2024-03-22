#include "scheduler.h"
#include "gps.h"
#include "serial_device.h"

int main() {
    EAR::Scheduler scheduler;
    GPS gps[2];
    SerialDevice serdev[2];
    
    gps[0].setIODevice(&serdev[0]);
    gps[1].setIODevice(&serdev[1]);
    
    if (!scheduler.add(&gps[0], 500000U) || !scheduler.add(&gps[1], 400000U)) {
	return -1;
    }

    if (!scheduler.start()) { return -1; }
    spdlog::info("scheduler running");

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if (!scheduler.stop()) { return -1; }
    spdlog::info("schedulers terminated");
  
    return 0;
}
