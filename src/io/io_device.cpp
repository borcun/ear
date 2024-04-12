#include "io_device.h"

EAR::IODevice::IODevice() { }

EAR::IODevice::~IODevice() { }

std::string EAR::IODevice::getModel() const {
    return m_model;
}

std::string EAR::IODevice::getVersion() const {
    return m_version;
}

int32_t EAR::IODevice::initialize() {
    return -1;
}

int32_t EAR::IODevice::shutdown() {
    return -1;
}

int32_t EAR::IODevice::receive(uint8_t *buf, const uint32_t size) {
    return -1;
}

int32_t EAR::IODevice::transmit(const uint8_t *buf, const uint32_t size) {
    return -1;
}

int32_t EAR::IODevice::configure(void *target, const int32_t op) {
    return -1;
} 
