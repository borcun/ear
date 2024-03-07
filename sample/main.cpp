#include <iostream>
#include "eth_service.h"
#include "file_service.h"
#include "gps.h"
#include <unistd.h>

int main() {
  EthernetService eth_service("ethernet service");
  FileService file_service("file service");
  GPS gps("gps device");

  gps.setIOService(&eth_service);

  if (gps.start()) {
      std::cout << "gps device is started" << std::endl;
  }
  
  usleep(5000000);

  if (gps.stop()) {
      std::cout << "gps device is stopped" << std::endl;
  }

  return 0;
}
