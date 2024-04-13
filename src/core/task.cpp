#include "task.h"

static uint32_t uuid = 0;

int EAR::doParallel(void *args) {
  ((EAR::Task *) args)->execute();
  return 0;
}

EAR::Task::Task()
    : m_is_running(false),
      m_period(std::chrono::microseconds(TASK_MIN_PERIOD))
{
    m_id = ++uuid;

    mtx_init(&m_mutex, mtx_plain);
    cnd_init(&m_cond_var);
    thrd_create(&m_task, doParallel, this);
}

EAR::Task::~Task() {
    thrd_join(m_task, nullptr);
    cnd_destroy(&m_cond_var);
    mtx_destroy(&m_mutex);
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
    cnd_signal(&m_cond_var);
    
    return true;
}

bool EAR::Task::restart() {
    cnd_signal(&m_cond_var);   
    return true;
}

bool EAR::Task::stop() {
    m_is_running = false;
    spdlog::debug("stop flag up for task {}", getId());

    // running flag is set to false, but be sure about releasing
    // if the task is blocked on condition variable
    cnd_signal(&m_cond_var);
    
    return true;
}
