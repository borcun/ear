#include "spdlog/spdlog.h"
#include "eth_service.h"
#include "file_service.h"
#include "serial_service.h"
#include "gpio_service.h"
#include "gps.h"
#include "logger.h"
#include "imu.h"
#include "switch.h"
#include "ssched.h"

int main() {
  FACE::ServiceScheduler *ss = FACE::ServiceScheduler::getInstance();   
  GPS gps("gps device");
  Logger logger("logger");
  IMU imu("imu device");
  Switch swi("switch");
  EthernetService eth_service("ethernet service");
  FileService file_service("file service");
  SerialService serial_service("serial service");
  GPIOService gpio_service("gpio service");
      
  gps.setIOService(&eth_service);
  logger.setIOService(&file_service);
  imu.setIOService(&serial_service);
  swi.setIOService(&gpio_service);

  gps.setPeriod(std::chrono::microseconds(100000));    // 100 ms
  logger.setPeriod(std::chrono::microseconds(200000)); // 200 ms
  imu.setPeriod(std::chrono::microseconds(300000));    // 300 ms
  swi.setPeriod(std::chrono::microseconds(500000));    // 500 ms
  
  if (!ss->addService(&gps)) { return -1; }
  if (!ss->addService(&logger)) { return -1; }
  if (!ss->addService(&imu)) { return -1; }
  if (!ss->addService(&swi)) { return -1; }

  spdlog::info("scheduler initializes");
  if (!ss->init()) { return -1; }
  
  spdlog::info("scheduler is running");
  if (!ss->run()) { return -1; }

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  if (!ss->terminate()) { return -1; }
  spdlog::info("scheduler terminated");
  
  return 0;
}
