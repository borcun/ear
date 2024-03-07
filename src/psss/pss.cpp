#include <iostream>
#include "pss.h"

/// base id value for platform specific service
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

bool FACE::PSSS::PlatformService::start(const std::chrono::microseconds &period) {
    if (m_is_started || period < std::chrono::microseconds(PSS_MIN_PERIOD)) {
	return false;
    }

    m_is_started = true;
    m_period = period;
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
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::microseconds elapsed;
    
    while (m_is_started) {
	begin = std::chrono::steady_clock::now();
	process();
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
    }

    return;
}
