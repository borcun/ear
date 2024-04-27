#include "scheduler.h"
#include "dcu.h"
#include "gps.h"
#include "serial_device.h"

int main() {
    EAR::Schedule::Scheduler scheduler;
    GPS gps1;
    GPS gps2;
    DCU dcu;
    SerialDevice dev1;
    SerialDevice dev2;

    spdlog::set_level(spdlog::level::debug);
    
    gps1.setDevice(&dev1);
    gps2.setDevice(&dev2);
    
    if (!scheduler.add(&gps1, 1000000U, 0U) ||
	!scheduler.add(&gps2, 2000000U, 0U) ||
	!scheduler.add(&dcu,  4000000U, 0U)) {
	return -1;
    }

    if (!scheduler.start()) { return -1; }
    spdlog::info("scheduler running");

    std::this_thread::sleep_for(std::chrono::milliseconds(13000));

    if (!scheduler.stop()) { return -1; }
    spdlog::info("schedulers terminated");
    
    return 0;
}
