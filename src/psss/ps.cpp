#include "ps.h"

//! current id value added to base service id for each platform specific service
static uint16_t curr_id = 0;

FACE::PSSS::PlatformService::PlatformService(const std::string &name) : EdgeService(name), APeriodicTask(name) {
  m_id = PS_BASE_ID + curr_id++;
}

FACE::PSSS::PlatformService::~PlatformService() {
    m_ioservice = nullptr;
}

void FACE::PSSS::PlatformService::setIOService(FACE::IOSS::IOService *ioservice) {
    m_ioservice = ioservice;
    return;
}

void FACE::PSSS::PlatformService::process() {
    spdlog::warn("process not overriden [service: {}]", EdgeService::getName());
    return;
}
