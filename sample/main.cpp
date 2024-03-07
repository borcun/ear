#include <iostream>
#include "eth_service.h"
#include "file_service.h"
#include "gps.h"
#include "logger.h"

int main() {
  EthernetService eth_service("ethernet service");
  FileService file_service("file service");
  GPS gps("gps device");
  Logger logger("logger");
      
  gps.setIOService(&eth_service);
  logger.setIOService(&file_service);

  if (!gps.start(std::chrono::microseconds(200000))) {
      std::cout << "could not start gps device" << std::endl;
      return -1;
  }

  std::cout << "gps device is started" << std::endl;
  
  if (!logger.start(std::chrono::microseconds(300000))) {
      std::cout << "could not start logger" << std::endl;
      return -1;
  }

  std::cout << "logger is started" << std::endl;
  
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  if (!gps.stop()) {
      std::cout << "could not stop gps device" << std::endl;
      return -1;
  }

  std::cout << "gps device is stopped" << std::endl;

  if (!logger.stop()) {
      std::cout << "could not stop logger" << std::endl;
      return -1;
  }

  std::cout << "logger is stopped" << std::endl;

  return 0;
}
