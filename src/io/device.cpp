#include "device.h"

EAR::IO::Device::Device(const std::string &name, const std::string &model, const std::string &version)
    : m_name(name), m_model(model), m_version(version)
{
}

EAR::IO::Device::~Device() {
    spdlog::debug("{} device terminated", toString());
}

std::string EAR::IO::Device::getName() const {
    return m_name;
}

std::string EAR::IO::Device::getModel() const {
    return m_model;
}

std::string EAR::IO::Device::getVersion() const {
    return m_version;
}

EAR::IO::State EAR::IO::Device::getState() const {
    return m_state;
}

int32_t EAR::IO::Device::initialize() {
    spdlog::warn("unimplemented function call [{}]", toString());
    return -1;
}

int32_t EAR::IO::Device::shutdown() {
    spdlog::warn("unimplemented function call [{}]", toString());
    return -1;
}

int32_t EAR::IO::Device::receive(void *buf, const uint32_t size) {
    spdlog::warn("unimplemented function call [{}]", toString());
    return -1;
}

int32_t EAR::IO::Device::transmit(const void *buf, const uint32_t size) {
    spdlog::warn("unimplemented function call [{}]", toString());
    return -1;
}

int32_t EAR::IO::Device::configure(void *target, const int32_t op) {
    spdlog::warn("unimplemented function call [{}]", toString());
    return -1;
} 

std::string EAR::IO::Device::toString() {
    return m_name + " (model: " + m_model + ", version: " + m_version + ")";
}
