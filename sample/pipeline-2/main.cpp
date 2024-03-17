#include "scheduler.h"
#include "bit.h"
#include "gps.h"
#include "serial_service.h"

int main() {
    FACE::Scheduler sched;
    BIT bit {new FACE::PCSS::PortableComponentService("BIT")};
    GPS gps_dev1 {"gps-dev-1"};
    GPS gps_dev2 {"gps-dev-2"};
    SerialService serial1 {"ser-serv-1"};
    SerialService serial2 {"ser-serv-2"};
    
    gps_dev1.setIOService(&serial1);
    gps_dev2.setIOService(&serial2);

    bit.addHelperService(&gps_dev1);
    bit.addHelperService(&gps_dev2);
    
    if (!(bit.subscribe(&gps_dev1) && bit.subscribe(&gps_dev2))) { return -1; }   
    if (!sched.add(&bit, 500000U)) { return -1; }
    if (!bit.init()) { return -1; }
    
    spdlog::info("scheduler running");
    if (!sched.start()) { return -1; }
  
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if (!sched.stop()) { return -1; }
    spdlog::info("scheduler terminated");
  
    return 0;
}
