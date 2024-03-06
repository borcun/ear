#include <iostream>
#include "eth_service.h"
#include "file_service.h"

int main() {
  EthernetService eth_service("ethernet service");
  FileService file_service("file service");

  std::cout << eth_service.getName() << " : " << eth_service.getId() << std::endl;
  std::cout << file_service.getName() << " : " << file_service.getId() << std::endl;
  std::cout << eth_service.getModel() << " : " << eth_service.getVersion() << std::endl;
  std::cout << file_service.getModel() << " : " << file_service.getVersion() << std::endl;

  eth_service.open();
  file_service.open();
  
  eth_service.read(nullptr, 0);
  file_service.read(nullptr, 0);
  eth_service.write(nullptr, 0);
  file_service.write(nullptr, 0);
  eth_service.ioctl(nullptr, 0);
  file_service.ioctl(nullptr, 0);
  
  eth_service.close();
  file_service.close();

  return 0;
}
