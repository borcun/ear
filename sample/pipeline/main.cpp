#include "scheduler.h"
#include "positioning.h"
#include "serial_service.h"
#include "gps.h"

int main() {
    FACE::Scheduler dev_sched;
    FACE::Scheduler pcs_sched;
    Positioning pos1 {"pos-serv-1"};
    Positioning pos2 {"pos-serv-2"};
    GPS gps {"gps-dev-1"};
    SerialService ser_serv_1 {"ser-serv-1"};
    
    gps.setIOService(&ser_serv_1);
    
    if (!(pos1.connect(&gps) && pos2.connect(&gps))) {
	return -1;
    }

    if (!dev_sched.add(&gps, 100000U)) {
	return -1;
    }
    
    if (!pcs_sched.add(&pos1, 100000U) ||
	!pcs_sched.add(&pos2, 100000U)) {
	return -1;
    }

    spdlog::info("schedulers initialize");
  
    if (!dev_sched.init())  { return -1; }
    if (!pcs_sched.init()) { return -1; }
  
    spdlog::info("schedulers are running");

    if (!dev_sched.run())  { return -1; }
    if (!pcs_sched.run()) { return -1; }

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    if (!pcs_sched.terminate()) { return -1; }
    if (!dev_sched.terminate())  { return -1; }
  
    spdlog::info("schedulers terminated");
  
    return 0;
}
