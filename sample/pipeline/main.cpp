#include "scheduler.h"
#include "localization.h"
#include "gps.h"
#include "serial_service.h"

int main() {
    FACE::Scheduler sched1;
    FACE::Scheduler sched2;
    Localization localization1 {"localization1"};
    Localization localization2 {"localization2"};
    GPS gps1 {"gps1"};
    GPS gps2 {"gps2"};
    GPS gps3 {"gps3"};
    SerialService serdev1, serdev2, serdev3;
    
    gps1.setIOService(&serdev1);
    gps2.setIOService(&serdev2);
    gps3.setIOService(&serdev3);
    localization1.subscribe(&gps1, 0); // no timeout
    localization1.subscribe(&gps2, 0);
    localization2.subscribe(&gps3, 0);
    
    if (!sched1.add(&localization1, 500000U) ||
	!sched1.add(&localization2, 500000U) ||
	!sched2.add(&gps1, 250000U) ||
	!sched2.add(&gps2, 500000U) || 
	!sched2.add(&gps3, 500000U)) {
	return -1;
    }

    if (!sched2.start()) { return -1; }
    spdlog::info("scheduler running");
    if (!sched1.start()) { return -1; }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if (!sched1.stop()) { return -1; }
    if (!sched2.stop()) { return -1; }
    spdlog::info("schedulers terminated");
  
    return 0;
}
