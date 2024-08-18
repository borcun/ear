#include "serial_device.h"
#include <cstring>

SerialDevice::SerialDevice(const std::string &name, const std::string &model, const std::string &version)
    : EAR::IO::Device(name, model, version)
{
}

SerialDevice::~SerialDevice() {

}

int32_t SerialDevice::initialize(void) {
  return 0;
}

int32_t SerialDevice::shutdown(void) {
  return 0;
}

int32_t SerialDevice::receive(void *buf, const uint32_t size) {
    uint8_t *_buf = (uint8_t *) buf;
    
    memset(_buf, 0x00, size);
    memcpy(_buf, &pos, sizeof(pos));

    pos.lon += 1.0f;
    pos.lat += 4.0f;
    
    return sizeof(pos);
}

int32_t SerialDevice::transmit(const void *buf, const uint32_t size) {
  return 0;
}

int32_t SerialDevice::configure(void *target, const int32_t op) {
  return 0;
}
