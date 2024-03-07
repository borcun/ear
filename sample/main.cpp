#include <iostream>
#include "eth_service.h"
#include "file_service.h"
#include "gps.h"

int main() {
  EthernetService eth_service("ethernet service");
  FileService file_service("file service");
  GPS gps("gps device");
      
  gps.setIOService(&eth_service);

  if (!gps.start(std::chrono::microseconds(200000))) {
      std::cout << "could not start gps device" << std::endl;
      return -1;
  }

  std::cout << "gps device is started" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(20000));

  if (!gps.stop()) {
      std::cout << "could not stop gps device" << std::endl;
      return -1;
  }

  std::cout << "\ngps device is stopped" << std::endl;

  return 0;
}
