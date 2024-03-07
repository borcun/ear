#include "file_service.h"

FileService::FileService(const std::string &name) : IOService(name) {
  m_model = "File Model";
  m_version = "1.0";
}

FileService::~FileService() {

}

int32_t FileService::open() {
  return 0;
}

int32_t FileService::close() {
  return 0;
}

int32_t FileService::read(uint8_t *buf, const uint32_t size) {
  return 0;
}

int32_t FileService::write(const uint8_t *buf, const uint32_t size) {
  return 0;
}

int32_t FileService::ioctl(void *target, const int32_t op) {
  return 0;
}
