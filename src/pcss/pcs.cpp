#include "pcs.h"

//! current id value added to base service id for each platform specific service
static uint16_t curr_id = 0;

FACE::PCSS::PortableComponentService::PortableComponentService(const std::string &name) : EdgeService(name), PeriodicTask(name) {
    m_id = PCS_BASE_ID + curr_id++;
}

FACE::PCSS::PortableComponentService::~PortableComponentService() {

}

void FACE::PCSS::PortableComponentService::process() {
    spdlog::warn("process not overriden [service: {}]", EdgeService::getName());
    return;
}
