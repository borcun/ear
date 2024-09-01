#include "itask.h"

/// unique id assigned to each task
static uint32_t uid = 0;

EAR::Schedule::ITask::ITask(const std::string &name) {
  m_id = ++uid;
  m_is_running = false;
  m_period = std::chrono::microseconds(TASK_MIN_PERIOD);
  // if user pass empty string for name, set its name to task-<id>
  m_name = name.empty() ? "task-" + std::to_string(m_id) : name;
    
  pthread_mutex_init(&m_start_mutex, nullptr);
  pthread_cond_init(&m_start_cond_var, nullptr);
  
  spdlog::debug("task {} created", name);
}

EAR::Schedule::ITask::~ITask() {
  pthread_cond_destroy(&m_start_cond_var);
  pthread_mutex_destroy(&m_start_mutex);
  
  spdlog::debug("task {} terminated", getName());
}

uint32_t EAR::Schedule::ITask::getId(void) const {
  return m_id;
}

std::string EAR::Schedule::ITask::getName(void) const {
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
    
bool EAR::Schedule::ITask::start(void) {
  if (m_is_running) {
    spdlog::error("could not start task {} already running", getName());
    return false;
  }

  m_is_running = true;
  pthread_cond_signal(&m_start_cond_var);
    
  return true;
}

bool EAR::Schedule::ITask::stop(void) {
  if (!m_is_running) {
    spdlog::error("could not stop task {} not running", getName());
    return false;
  }

  m_is_running = false;
  spdlog::debug("task {} stop flag is up", getName());
    
  return true;
}
