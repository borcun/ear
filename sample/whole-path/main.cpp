#include "spdlog/spdlog.h"
#include "positioning.h"
#include "serial_service.h"
#include "gps.h"
#include "ssched.h"

int main() {
  FACE::ServiceScheduler ps_scheduler;
  FACE::ServiceScheduler pcs_scheduler;
  
  SerialService serial_service1("serial service");
  GPS gps1("gps device");
  FACE::TSS::TransportService ts1("pos channel");
  Positioning positioning1("pos-serv-1");

  SerialService serial_service2("serial service");
  GPS gps2("gps device");
  FACE::TSS::TransportService ts2("pos channel");
  Positioning positioning2("pos-serv-2");

  gps1.setIOService(&serial_service1);
  gps2.setIOService(&serial_service2);
  gps1.setTransportService(&ts1);
  gps2.setTransportService(&ts2);
  gps1.setPeriod(std::chrono::microseconds(500000));    // 100 ms
  gps2.setPeriod(std::chrono::microseconds(500000));    // 100 ms

  positioning1.setTransportService(&ts1);
  positioning2.setTransportService(&ts2);
  positioning1.setPeriod(std::chrono::microseconds(1000000));    // 100 ms
  positioning2.setPeriod(std::chrono::microseconds(1000000));    // 100 ms
  
  if (!ps_scheduler.addService(&gps1)) { return -1; }
  if (!ps_scheduler.addService(&gps2)) { return -1; }
  if (!pcs_scheduler.addService(&positioning1)) { return -1; }
  if (!pcs_scheduler.addService(&positioning2)) { return -1; }

  spdlog::info("schedulers initialize");
  if (!ps_scheduler.init()) { return -1; }
  if (!pcs_scheduler.init()) { return -1; }
  
  spdlog::info("schedulers are running");
  if (!ps_scheduler.run()) { return -1; }
  usleep(500000);
  if (!pcs_scheduler.run()) { return -1; }

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  if (!ps_scheduler.terminate()) { return -1; }
  if (!pcs_scheduler.terminate()) { return -1; }
  spdlog::info("schedulers terminated");
  
  return 0;
}
