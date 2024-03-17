#include "task.h"

FACE::Task::Task(const std::string &name)
    : m_name(name),
      m_is_running(false),
      m_period(std::chrono::microseconds(TASK_MIN_PERIOD))
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond_var, NULL);
  
    m_task = std::thread([=] { this->execute(); });
}

FACE::Task::~Task() {
    pthread_cond_destroy(&m_cond_var);
    pthread_mutex_destroy(&m_mutex);
}

const std::string &FACE::Task::getName() const {
    return m_name;
}

void FACE::Task::setPeriod(const std::chrono::microseconds &period) {
    m_period = std::chrono::microseconds(period);
    return;
}

bool FACE::Task::start() {
    if (m_is_running) {
	spdlog::error("task already running [{}]", m_name);
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
    // if waiting task existing
    pthread_cond_signal(&m_cond_var);
    m_task.join();

    return true;
}
