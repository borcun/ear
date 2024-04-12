#include "serial_device.h"
#include <cstring>

SerialDevice::SerialDevice() : EAR::IODevice() {
    m_model = "Serial Model";
    m_version = "1.0";
}

SerialDevice::~SerialDevice() {

}

int32_t SerialDevice::initialize() {
    return 0;
}

int32_t SerialDevice::shutdown() {
    return 0;
}

int32_t SerialDevice::receive(uint8_t *buf, const uint32_t size) {
    memset(buf, 0x00, size);
    memcpy(buf, &pos, sizeof(pos));

    pos.lon += 1.0f;
    pos.lat += 4.0f;
    
    return sizeof(pos);
}

int32_t SerialDevice::transmit(const uint8_t *buf, const uint32_t size) {
    return 0;
}

int32_t SerialDevice::configure(void *target, const int32_t op) {
    return 0;
}
