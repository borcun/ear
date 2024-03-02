#include "ios.h"

//! base id value for io service
#define IO_SERVICE_BASE_ID (100U)

//! current id value added to base service id for each io service
static uint8_t _ios_local_id = 0;

IOSS::IOService::IOService(const std::string &name) : FACE::Service(name) {
  m_id = IO_SERVICE_BASE_ID + _ios_local_id++;
}

IOSS::IOService::~IOService() {

}

std::string IOSS::IOService::getModel() const {
  return m_model;
}

std::string IOSS::IOService::getVersion() const {
  return m_version;
}

int32_t IOSS::IOService::open() {
  return -1;
}

int32_t IOSS::IOService::close() {
  return -1;
}

int32_t IOSS::IOService::read(uint8_t *buf, const uint32_t size) {
  return -1;
}

int32_t IOSS::IOService::write(const uint8_t *buf, const uint32_t size) {
  return -1;
}

int32_t IOSS::IOService::ioctl(void *target, const int32_t op) {
  return -1;
} 
