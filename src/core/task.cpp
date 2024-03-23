#include "task.h"

static uint32_t uuid = 0;

EAR::Task::Task()
    : m_is_running(false),
      m_period(std::chrono::microseconds(TASK_MIN_PERIOD))
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond_var, NULL);

    m_id = ++uuid;
    m_task = std::thread([=] { this->execute(); });
}

EAR::Task::~Task() {
    pthread_cond_destroy(&m_cond_var);
    pthread_mutex_destroy(&m_mutex);
}

uint32_t EAR::Task::getId() const {
    return m_id;
}

void EAR::Task::setPeriod(const std::chrono::microseconds period) {
    m_period = std::chrono::microseconds(period);
    return;
}

void EAR::Task::setOffset(const std::chrono::microseconds offset) {
    m_offset = std::chrono::microseconds(offset);
    return;
}

bool EAR::Task::start() {
    if (m_is_running) {
	spdlog::error("task {} already running", m_id);
	return false;
    }

    m_is_running = true;
    pthread_cond_signal(&m_cond_var);
    
    return true;
}

bool EAR::Task::restart() {
    pthread_cond_signal(&m_cond_var);   
    return true;
}

bool EAR::Task::stop() {
    m_is_running = false;
    spdlog::debug("running flag down for task {}", m_id);
    // if waiting task existing
    pthread_cond_signal(&m_cond_var);
    spdlog::debug("condition signal triggered for task {}", m_id);
    m_task.join();
    spdlog::debug("task {} joined", m_id);
    
    return true;
}
