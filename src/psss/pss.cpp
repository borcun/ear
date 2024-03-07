#include <iostream>
#include <unistd.h>
#include "pss.h"

//! base id value for platform specific service
#define PSS_BASE_ID (2000U)

//! current id value added to base service id for each platform specific service
static uint8_t __pss_local_id = 0;

FACE::PSSS::PlatformService::PlatformService(const std::string &name) : Service(name) {
  m_id = PSS_BASE_ID + __pss_local_id++;
}

FACE::PSSS::PlatformService::~PlatformService() {
    m_ioservice = nullptr;
    m_tservice = nullptr;
}

void FACE::PSSS::PlatformService::setIOService(FACE::IOSS::IOService *ioservice) {
    m_ioservice = ioservice;
}

void FACE::PSSS::PlatformService::setTransportService(FACE::TSS::TransportService *tservice) {
    m_tservice = tservice;
}

bool FACE::PSSS::PlatformService::start() {
    if (m_is_started) {
	return false;
    }

    m_is_started = true;
    m_task = std::thread([this] { this->schedule(); });
    
    return true;
}

bool FACE::PSSS::PlatformService::stop() {
    if (!m_is_started) {
	return false;
    }

    m_is_started = false;
    m_task.join();

    return true;
}

void FACE::PSSS::PlatformService::process() {
    return;
}

void FACE::PSSS::PlatformService::schedule() {
    while (m_is_started) {
	process();

	/// @todo sleep by period
	usleep(1000000);
    }

    return;
}
