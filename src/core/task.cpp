#include "task.h"

static uint32_t id = 0;

FACE::Task::Task()
    : m_is_running(false),
      m_period(std::chrono::microseconds(TASK_MIN_PERIOD))
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond_var, NULL);

    m_id = ++id;
    m_task = std::thread([=] { this->execute(); });
}

FACE::Task::~Task() {
    pthread_cond_destroy(&m_cond_var);
    pthread_mutex_destroy(&m_mutex);
}

uint32_t FACE::Task::getId() const {
    return m_id;
}

void FACE::Task::setPeriod(const std::chrono::microseconds &period) {
    m_period = std::chrono::microseconds(period);
    return;
}

bool FACE::Task::start() {
    if (m_is_running) {
	spdlog::error("task {} already running", id);
	return false;
    }

    m_is_running = true;
    pthread_cond_signal(&m_cond_var);
    
    return true;
}

bool FACE::Task::restart() {
    pthread_cond_signal(&m_cond_var);   
    return true;
}

bool FACE::Task::stop() {
    m_is_running = false;
    spdlog::debug("running flag down for task {}", m_id);
    // if waiting task existing
    pthread_cond_signal(&m_cond_var);
    spdlog::debug("condition signal triggered for task {}", m_id);
    m_task.join();
    spdlog::debug("task {} joined", m_id);
    
    return true;
}
