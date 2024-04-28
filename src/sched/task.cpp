#include "task.h"

static uint32_t uuid = 0;

void *EAR::Schedule::doParallel(void *args) {
  ((EAR::Schedule::Task *) args)->execute();
  return nullptr;
}

EAR::Schedule::Task::Task()
    : m_is_running(false),
      m_period(std::chrono::microseconds(TASK_MIN_PERIOD))
{
    m_id = ++uuid;

    pthread_mutex_init(&m_start_mutex, nullptr);
    pthread_mutex_init(&m_progress_mutex, nullptr);
    pthread_cond_init(&m_start_cond_var, nullptr);
    pthread_cond_init(&m_progress_cond_var, nullptr);
    
    pthread_create(&m_task, nullptr, doParallel, this);
}

EAR::Schedule::Task::~Task() {
    pthread_join(m_task, nullptr);

    pthread_cond_destroy(&m_start_cond_var);
    pthread_cond_destroy(&m_progress_cond_var);
    pthread_mutex_destroy(&m_start_mutex);
    pthread_mutex_destroy(&m_progress_mutex);
}

uint32_t EAR::Schedule::Task::getId() const {
    return m_id;
}

void EAR::Schedule::Task::setPeriod(const std::chrono::microseconds period) {
    m_period = std::chrono::microseconds(period);
    return;
}

void EAR::Schedule::Task::setOffset(const std::chrono::microseconds offset) {
    m_offset = std::chrono::microseconds(offset);
    return;
}

bool EAR::Schedule::Task::start() {
    if (m_is_running) {
	spdlog::error("task {} already running", getId());
	return false;
    }

    m_is_running = true;
    while (0 != pthread_cond_signal(&m_start_cond_var));
    
    return true;
}

bool EAR::Schedule::Task::restart() {
    if (!m_is_running) {
	return false;
    }
    
    while (0 != pthread_cond_signal(&m_progress_cond_var));
    return true;
}

bool EAR::Schedule::Task::stop() {
    if (!m_is_running) {
	return false;
    }

    m_is_running = false;
    spdlog::debug("stop flag up for task {}", getId());

    // running flag is set to false, but be sure about releasing
    // if the task is blocked on condition variable
    while (0 != pthread_cond_signal(&m_progress_cond_var));
    
    return true;
}
