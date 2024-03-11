#include "ps.h"

//! current id value added to base service id for each platform specific service
static uint16_t curr_id = 0;

FACE::PSSS::PlatformService::PlatformService(const std::string &name) : PeriodicService(name) {
  m_id = PS_BASE_ID + curr_id++;
}

FACE::PSSS::PlatformService::~PlatformService() {
    m_ioservice = nullptr;
    m_tservice = nullptr;
}

void FACE::PSSS::PlatformService::setIOService(FACE::IOSS::IOService *ioservice) {
    m_ioservice = ioservice;
    return;
}

void FACE::PSSS::PlatformService::setTransportService(FACE::TSS::TransportService *tservice) {
    m_tservice = tservice;
    return;
}

void FACE::PSSS::PlatformService::service() {
    spdlog::warn("service not implemented [service: {}]", getName());
    return;
}
