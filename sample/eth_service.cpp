#include <iostream>
#include "eth_service.h"

EthernetService::EthernetService(const std::string &name) : IOService(name) {
  m_model = "Ethernet Model";
  m_version = "1.0";
}

EthernetService::~EthernetService() {
  std::cout << __FILE__ << ": " << __FUNCTION__ << std::endl;
}

int32_t EthernetService::open() {
  std::cout << __FILE__ << ": " << __FUNCTION__ << std::endl;
  return 0;
}

int32_t EthernetService::close() {
  std::cout << __FILE__ << ": " << __FUNCTION__ << std::endl;
  return 0;
}

int32_t EthernetService::read(uint8_t *buf, const uint32_t size) {
  std::cout << __FILE__ << ": " << __FUNCTION__ << std::endl;
  return 0;
}

int32_t EthernetService::write(const uint8_t *buf, const uint32_t size) {
  std::cout << __FILE__ << ": " << __FUNCTION__ << std::endl;
  return 0;
}

int32_t EthernetService::ioctl(void *target, const int32_t op) {
  std::cout << __FILE__ << ": " << __FUNCTION__ << std::endl;
  return 0;
}
