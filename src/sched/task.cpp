#include "sched/task.h"
#include "spdlog/spdlog.h"

/// unique id assigned to each task
static uint32_t uid = 0;

EAR::Schedule::Task::Task(const std::string &name)
  : m_task_ready(false)
{
  ++uid;
  
  if (name.empty()) {
    m_name = "task-" + std::to_string(uid);
  }
  else {
    m_name = name;
  }
}

EAR::Schedule::Task::~Task() {
}

std::string EAR::Schedule::Task::getName(void) const {
  return m_name;
}

void EAR::Schedule::Task::setPeriod(const std::chrono::microseconds period) {
  m_period = std::chrono::microseconds(period);
  return;
}

void EAR::Schedule::Task::setOffset(const std::chrono::microseconds offset) {
  m_offset = std::chrono::microseconds(offset);
  return;
}

void EAR::Schedule::Task::setConditionVariable(std::condition_variable *cond_var) {
  m_cond_var = cond_var;
  return;
}

bool EAR::Schedule::Task::operator==(const Task &other) const {
  return 0 == getName().compare(other.getName());
}

bool EAR::Schedule::Task::operator!=(const Task &other) const {
  return !(*this == other);
}

bool EAR::Schedule::Task::start(void) {
  if (m_is_running) {
    spdlog::error("could not start task {} already running", getName());
    return false;
  }

  if (nullptr == m_cond_var) {
    spdlog::error("could not start task {} unless condition variable is set", getName());
    return false;
  }

  m_is_running = true;
  
  m_task = std::thread(&Task::execute, this);

  // wait until thread function is active
  while (!m_task_ready.load(std::memory_order_acquire)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  return true;
}

bool EAR::Schedule::Task::stop(void) {
  if (!m_is_running) {
    spdlog::error("could not stop task {} not running", getName());
    return false;
  }

  m_task_ready.store(false, std::memory_order_release);  
  m_is_running = false;
  
  m_task.join();

  return true;
}

void EAR::Schedule::Task::execute(void) {
  std::chrono::steady_clock::time_point begin;
  std::chrono::steady_clock::time_point end;
  std::chrono::microseconds elapsed;
  std::unique_lock<std::mutex> ulock(m_mutex);

  // signal readiness for start function
  m_task_ready.store(true, std::memory_order_release);
  
  m_cond_var->wait(ulock);
  std::this_thread::sleep_for(std::chrono::microseconds(m_offset));
    
  do {
    begin = std::chrono::steady_clock::now();
    cycle();
    end = std::chrono::steady_clock::now();
	
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    if (elapsed <= m_period) {
      std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
    }
    else {
      spdlog::error("deadline missed for task {}", getName());
      std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
    }
  } while (m_is_running);

  spdlog::debug("task {} is being stopped", getName());
    
  return;
}
