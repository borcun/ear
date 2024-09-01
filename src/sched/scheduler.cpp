#include "scheduler.h"

EAR::Schedule::Scheduler::Scheduler(const std::string &name) : m_name(name) {
  m_state = SCHEDULER_IDLE;
  spdlog::debug("scheduler {} created", m_name);
}

EAR::Schedule::Scheduler::~Scheduler() {
  spdlog::debug("scheduler {} terminated", getName());
}

std::string EAR::Schedule::Scheduler::getName(void) const {
  return m_name;
}

bool EAR::Schedule::Scheduler::allocate(Task *task, const uint32_t period, const uint32_t offset) {
  if (nullptr == task) {
    spdlog::error("could not allocate memory for null task in {}", getName());
    return false;
  }

  if (period < TASK_MIN_PERIOD) {
    spdlog::error("invalid period value {} for task {}", period, task->getName());
    return false;
  }

  if (SCHEDULER_IDLE != m_state) {
    spdlog::error("could not allocate memory for {} when scheduler {} run", task->getName(), getName());
    return false;
  }

  auto pair = m_tasks.insert(task);

  if (!pair.second) {
    spdlog::error("could not allocate task {}, it was already allocated", task->getName());
    return false;
  }

  task->setPeriod(std::chrono::microseconds(period));
  task->setOffset(std::chrono::microseconds(offset));

  if (!task->initialize()) {
    spdlog::error("could not initialize task {} in {}", task->getName(), getName());
    return false;	
  }
        
  return true;
}

bool EAR::Schedule::Scheduler::start(void) {
  if (SCHEDULER_IDLE != m_state) {
    spdlog::error("could not run the scheduler {} that was already running", getName());
    return false;
  }

  if (0 == m_tasks.size()) {
    spdlog::error("could not run the scheduler {} that not include any task", getName());
    return false;
  }

  for (auto &task : m_tasks) {
    if (!task->start()) {
      spdlog::critical("could not start task {}", task->getName());
    }
    else {
      spdlog::debug("tasks {} started", task->getName());
    }
  }

  m_state = SCHEDULER_RUN;
  return true;
}

bool EAR::Schedule::Scheduler::stop(void) {
  if (SCHEDULER_RUN != m_state) {
    spdlog::error("could not stop the scheduler {} that not running", getName());
    return false;
  }
    
  for (auto &task : m_tasks) {
    if (!task->stop()) {
      spdlog::critical("could not stop task {}", task->getName());
    }
    else {
      spdlog::debug("task {} stopped", task->getName());
    }
  }

  m_state = SCHEDULER_IDLE;
  return true;
}
