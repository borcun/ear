#include "scheduler.h"
#include "positioning.h"
#include "serial_service.h"
#include "gps.h"

int main() {
    FACE::Scheduler dev_sched;
    FACE::Scheduler pcs_sched;
    Positioning pos1 {"pos-serv-1"};
    Positioning pos2 {"pos-serv-2"};
    Positioning pos3 {"pos-serv-3"};
    GPS gps1 {"gps-dev-1"};
    GPS gps2 {"gps-dev-2"};
    SerialService serial1 {"ser-serv-1"};
    SerialService serial2 {"ser-serv-2"};
    
    gps1.setIOService(&serial1);
    gps2.setIOService(&serial2);
    
    if (!(pos1.connect(&gps1) && pos2.connect(&gps1) && pos3.connect(&gps2))) {
	return -1;
    }

    if (!dev_sched.add(&gps1, 100000U) ||
	!dev_sched.add(&gps2, 200000U)) {
	return -1;
    }
    
    if (!pcs_sched.add(&pos1, 100000U) ||
	!pcs_sched.add(&pos2, 100000U) ||
	!pcs_sched.add(&pos3, 200000U))	{
	return -1;
    }

    spdlog::info("schedulers initialize");
  
    if (!dev_sched.init())  { return -1; }
    if (!pcs_sched.init()) { return -1; }
  
    spdlog::info("schedulers are running");

    if (!dev_sched.run())  { return -1; }
    if (!pcs_sched.run()) { return -1; }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if (!pcs_sched.terminate()) { return -1; }
    if (!dev_sched.terminate())  { return -1; }
  
    spdlog::info("schedulers terminated");
  
    return 0;
}
