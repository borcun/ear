#include "ios.h"

FACE::IOSS::IOService::IOService() {

}

FACE::IOSS::IOService::~IOService() {

}

std::string FACE::IOSS::IOService::getModel() const {
    return m_model;
}

std::string FACE::IOSS::IOService::getVersion() const {
    return m_version;
}

int32_t FACE::IOSS::IOService::open() {
    return -1;
}

int32_t FACE::IOSS::IOService::close() {
    return -1;
}

int32_t FACE::IOSS::IOService::read(uint8_t *buf, const uint32_t size) {
    return -1;
}

int32_t FACE::IOSS::IOService::write(const uint8_t *buf, const uint32_t size) {
    return -1;
}

int32_t FACE::IOSS::IOService::ioctl(void *target, const int32_t op) {
    return -1;
} 
