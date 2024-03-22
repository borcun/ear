#include "serial_device.h"

SerialDevice::SerialDevice() : EAR::IODevice() {
    m_model = "Serial Model";
    m_version = "1.0";
}

SerialDevice::~SerialDevice() {

}

int32_t SerialDevice::open() {
    return 0;
}

int32_t SerialDevice::close() {
    return 0;
}

int32_t SerialDevice::read(uint8_t *buf, const uint32_t size) {
    memset(buf, 0x00, size);
    memcpy(buf, &pos, sizeof(pos));

    pos.lon += 1.0f;
    pos.lat += 4.0f;
    
    return sizeof(pos);
}

int32_t SerialDevice::write(const uint8_t *buf, const uint32_t size) {
    return 0;
}

int32_t SerialDevice::ioctl(void *target, const int32_t op) {
    return 0;
}
