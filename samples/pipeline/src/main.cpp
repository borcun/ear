#include "sched/scheduler.h"
#include "dcu_service.h"
#include "location_service.h"
#include "gps_device.h"
#include "serial_controller.h"
#include "spdlog/spdlog.h"

int main() {
  spdlog::set_level(spdlog::level::debug);
      
  EAR::Schedule::Scheduler scheduler("pipeline");
  DCUService dcu_service("dcu-service");
  LocationService location_service1("location-service 1");
  LocationService location_service2("location-service 2");
  GPSDevice gps_dev1("gps-device 1", "1", "1.0.0");
  GPSDevice gps_dev2("gps-device 2", "2", "1.0.0");
  SerialController serial_controller1("ser-ctrl 1");
  SerialController serial_controller2("ser-ctrl 2");

  // set controllers of devices
  gps_dev1.setController(&serial_controller1);
  gps_dev2.setController(&serial_controller2);
  // set devices of services
  location_service1.setDevice(&gps_dev1);
  location_service2.setDevice(&gps_dev2);
    
  if (!scheduler.allocate(&location_service1, 1000000U, 0U) ||
      !scheduler.allocate(&location_service2, 2000000U, 2000000U) ||
      !scheduler.allocate(&dcu_service,  3000000U, 3000000U))
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
