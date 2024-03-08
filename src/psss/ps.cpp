#include "ps.h"
#include <iostream>

/// base id value for platform specific service
#define PS_BASE_ID (2000U)

//! current id value added to base service id for each platform specific service
static uint8_t __ps_local_id = 0;

FACE::PSSS::PlatformService::PlatformService(const std::string &name) : Service(name) {
  m_id = PS_BASE_ID + __ps_local_id++;
  m_is_started = false;
  m_period = std::chrono::microseconds(PS_MIN_PERIOD);
  pthread_mutex_init(&m_mutex, NULL);
}

FACE::PSSS::PlatformService::~PlatformService() {
    m_ioservice = nullptr;
    m_tservice = nullptr;
    pthread_mutex_destroy(&m_mutex);
}

void FACE::PSSS::PlatformService::setIOService(FACE::IOSS::IOService *ioservice) {
    m_ioservice = ioservice;
    return;
}

void FACE::PSSS::PlatformService::setTransportService(FACE::TSS::TransportService *tservice) {
    m_tservice = tservice;
    return;
}

void FACE::PSSS::PlatformService::setPeriod(const std::chrono::microseconds &period) {
    // do not change service period when task is running
    if (!m_is_started) {
	m_period = std::chrono::microseconds(period);
    }
    
    return;
}

bool FACE::PSSS::PlatformService::start(pthread_cond_t *cond_var) {
    if (m_is_started) {
	return false;
    }

    m_is_started = true;
    m_task = std::thread([=] { this->execute(cond_var); });
    
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

void FACE::PSSS::PlatformService::service() {
    return;
}

void FACE::PSSS::PlatformService::execute(pthread_cond_t *cond_var) {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::microseconds elapsed;

    // wait order from scheduler
    pthread_cond_wait(cond_var, &m_mutex);
    
    while (m_is_started) {
	begin = std::chrono::steady_clock::now();
	service();
	end = std::chrono::steady_clock::now();
	
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	// sleep time remain after service execution
	std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
    }

    return;
}
