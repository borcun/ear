#include "scheduler.h"
#include "dcu.h"
#include "gps.h"
#include "serial_device.h"

int main() {
  spdlog::set_level(spdlog::level::debug);
      
    EAR::Schedule::Scheduler scheduler("pipeline");
    GPS gps1("GPS 1");
    GPS gps2("GPS 2");
    DCU dcu("DCU");
    SerialDevice dev1("serdev", "1", "1.0.0");
    SerialDevice dev2("serdev", "2", "1.0.0");
    
    gps1.setDevice(&dev1);
    gps2.setDevice(&dev2);
    
    if (!scheduler.allocate(&gps1, 1000000U, 0U) ||
	!scheduler.allocate(&gps2, 2000000U, 0U) ||
	!scheduler.allocate(&dcu,  4000000U, 0U))
	{
	    return -1;
	}

    if (!scheduler.start()) { return -1; }
    spdlog::info("scheduler running");

    std::this_thread::sleep_for(std::chrono::milliseconds(13000));

    if (!scheduler.stop()) { return -1; }
    spdlog::info("schedulers terminated");
    
    return 0;
}
