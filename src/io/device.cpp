#include "device.h"

EAR::IO::Device::Device() { }

EAR::IO::Device::~Device() { }

std::string EAR::IO::Device::getModel() const {
    return m_model;
}

std::string EAR::IO::Device::getVersion() const {
    return m_version;
}

int32_t EAR::IO::Device::initialize() {
    return -1;
}

int32_t EAR::IO::Device::shutdown() {
    return -1;
}

int32_t EAR::IO::Device::receive(void *buf, const uint32_t size) {
    return -1;
}

int32_t EAR::IO::Device::transmit(const void *buf, const uint32_t size) {
    return -1;
}

int32_t EAR::IO::Device::configure(void *target, const int32_t op) {
    return -1;
} 
