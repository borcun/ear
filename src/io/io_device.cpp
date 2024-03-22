#include "io_device.h"

EAR::IODevice::IODevice() {

}

EAR::IODevice::~IODevice() {

}

std::string EAR::IODevice::getModel() const {
    return m_model;
}

std::string EAR::IODevice::getVersion() const {
    return m_version;
}

int32_t EAR::IODevice::open() {
    return -1;
}

int32_t EAR::IODevice::close() {
    return -1;
}

int32_t EAR::IODevice::read(uint8_t *buf, const uint32_t size) {
    return -1;
}

int32_t EAR::IODevice::write(const uint8_t *buf, const uint32_t size) {
    return -1;
}

int32_t EAR::IODevice::ioctl(void *target, const int32_t op) {
    return -1;
} 
