#include "serial_service.h"

SerialService::SerialService() {
    m_model = "Serial Model";
    m_version = "1.0";
}

SerialService::~SerialService() {

}

int32_t SerialService::open() {
    return 0;
}

int32_t SerialService::close() {
    return 0;
}

int32_t SerialService::read(uint8_t *buf, const uint32_t size) {
    memset(buf, 0x00, size);
    memcpy(buf, &pos, sizeof(pos));

    pos.lon += 1.0f;
    pos.lat += 4.0f;
    
    return sizeof(pos);
}

int32_t SerialService::write(const uint8_t *buf, const uint32_t size) {
    return 0;
}

int32_t SerialService::ioctl(void *target, const int32_t op) {
    return 0;
}
