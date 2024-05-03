#include "scheduler.h"
#include "network_manager.h"
#include "dcu.h"
#include "gps.h"
#include "serial_device.h"

int main() {
    EAR::Schedule::Scheduler scheduler;
    EAR::Communication::NetworkManager netman("netman");
    GPS gps1("GPS 1");
    GPS gps2("GPS 2");
    DCU dcu("DCU");
    SerialDevice dev1("serdev", "1", "1.0.0");
    SerialDevice dev2("serdev", "2", "1.0.0");

    spdlog::set_level(spdlog::level::debug);

    if (!netman.initialize()) {
	spdlog::error("could not initialize network manager");
	return -1;
    }
    
    gps1.setDevice(&dev1);
    gps2.setDevice(&dev2);

    // network operations
    dcu.setServer(netman.getServer());
    gps1.setClient(netman.getClient());
    gps2.setClient(netman.getClient());
    
    if (!scheduler.allocate(&gps1, 1000000U, 0U) ||
	!scheduler.allocate(&gps2, 2000000U, 0U) ||
	!scheduler.allocate(&dcu,  2000000U, 0U)) {
	return -1;
    }

    if (!scheduler.start()) { return -1; }
    spdlog::info("scheduler running");

    std::this_thread::sleep_for(std::chrono::milliseconds(13000));

    if (!scheduler.stop()) { return -1; }
    spdlog::info("schedulers terminated");

    netman.terminate();
    
    return 0;
}
