#include "gpio_service.h"

GPIOService::GPIOService(const std::string &name) : IOService(name) {
  m_model = "GPIO Model";
  m_version = "1.0";
}

GPIOService::~GPIOService() {

}

int32_t GPIOService::open() {
  return 0;
}

int32_t GPIOService::close() {
  return 0;
}

int32_t GPIOService::read(uint8_t *buf, const uint32_t size) {
  return 0;
}

int32_t GPIOService::write(const uint8_t *buf, const uint32_t size) {
  return 0;
}

int32_t GPIOService::ioctl(void *target, const int32_t op) {
  return 0;
}
