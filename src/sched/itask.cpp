#include "itask.h"

static uint32_t uuid = 0;

EAR::Schedule::ITask::ITask(const std::string &name)
    : m_is_running(false),
      m_period(std::chrono::microseconds(TASK_MIN_PERIOD))
{
    m_id = ++uuid;
    m_name = name.empty() ? "task-" + std::to_string(m_id) : name;

    pthread_mutex_init(&m_start_mutex, nullptr);
    pthread_mutex_init(&m_progress_mutex, nullptr);
    pthread_cond_init(&m_start_cond_var, nullptr);
    pthread_cond_init(&m_progress_cond_var, nullptr);
}

EAR::Schedule::ITask::~ITask() {
    pthread_cond_destroy(&m_start_cond_var);
    pthread_cond_destroy(&m_progress_cond_var);
    pthread_mutex_destroy(&m_start_mutex);
    pthread_mutex_destroy(&m_progress_mutex);
}

uint32_t EAR::Schedule::ITask::getId() const {
    return m_id;
}

std::string EAR::Schedule::ITask::getName() const {
    return m_name;
}

void EAR::Schedule::ITask::setPeriod(const std::chrono::microseconds period) {
    m_period = std::chrono::microseconds(period);
    return;
}

void EAR::Schedule::ITask::setOffset(const std::chrono::microseconds offset) {
    m_offset = std::chrono::microseconds(offset);
    return;
}
    
bool EAR::Schedule::ITask::start() {
    if (m_is_running) {
	spdlog::error("task {} already running", getName());
	return false;
    }

    m_is_running = true;
    pthread_cond_signal(&m_start_cond_var);
    
    return true;
}

bool EAR::Schedule::ITask::stop() {
    if (!m_is_running) {
	return false;
    }

    m_is_running = false;
    spdlog::debug("stop flag up for task {}", getName());
    
    return true;
}
