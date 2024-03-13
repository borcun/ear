#include "portable_service.h"

//! current id value added to base service id for each platform specific service
static uint16_t curr_id = 0;

FACE::PortableService::PortableService(const std::string &name) : Service(name) {
  m_is_started = false;
  m_period = std::chrono::microseconds(SERVICE_MIN_PERIOD);
  pthread_mutex_init(&m_mutex, NULL);
}

FACE::PortableService::~PortableService() {
    pthread_mutex_destroy(&m_mutex);
}

void FACE::PortableService::setPeriod(const std::chrono::microseconds &period) {
    // do not change service period when task is running
    if (m_is_started) {
	spdlog::error("could not change period after start [service: {}]", getName());
    }
    else {
	m_period = std::chrono::microseconds(period);
    }
    
    return;
}

void FACE::PortableService::setChannel(FACE::TSS::Channel *channel) {
    m_channel = channel;
    return;
}

bool FACE::PortableService::start(pthread_cond_t *cond_var) {
    if (m_is_started) {
	spdlog::error("service already started [service: {}]", getName());
	return false;
    }

    m_is_started = true;
    m_task = std::thread([=] { this->execute(cond_var); });
    
    return true;
}

bool FACE::PortableService::stop() {
    if (!m_is_started) {
	spdlog::error("service already started [service: {}]", getName());
	return false;
    }

    m_is_started = false;
    m_task.join();

    return true;
}

void FACE::PortableService::service() {
    spdlog::warn("service not implemented [service: {}]", getName());
    return;
}

void FACE::PortableService::execute(pthread_cond_t *cond_var) {
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
	if (elapsed <= m_period) {
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
	}
	else {
	    spdlog::warn("deadline missed [service: {}]", getName());
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
	}
    }

    return;
}
