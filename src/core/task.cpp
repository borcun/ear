#include "task.h"

static uint32_t uuid = 0;

void *EAR::doParallel(void *args) {
  ((EAR::Task *) args)->execute();
  return NULL;
}

EAR::Task::Task()
    : m_is_running(false),
      m_period(std::chrono::microseconds(TASK_MIN_PERIOD))
{
    m_id = ++uuid;

    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond_var, NULL);
    pthread_create(&m_task, NULL, doParallel, this);
}

EAR::Task::~Task() {
    pthread_join(m_task, NULL);
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
	spdlog::error("task {} already running", getId());
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
    spdlog::debug("stop flag up for task {}", getId());

    // running flag is set to false, but be sure about releasing
    // if the task is blocked on condition variable
    pthread_cond_signal(&m_cond_var);
    
    return true;
}
