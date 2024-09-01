#include "task.h"

void *EAR::Schedule::__makeParallel(void *args) {
  if (nullptr == args) {
    spdlog::critical("could not start task, invalid task instance");
    return nullptr;
  }
  
  EAR::Schedule::Task *task = reinterpret_cast<EAR::Schedule::Task *>(args);
    
  if (nullptr == task) {
    spdlog::critical("could not start task, because conversion failed");
  }
  else {
    task->execute();
  }
    
  return nullptr;
}

EAR::Schedule::Task::Task(const std::string &name) : EAR::Schedule::Synchronizable(name) {
  if (0 != pthread_create(&m_task, nullptr, __makeParallel, this)) {
    spdlog::error("could not create task {}", getName());
  }
}

EAR::Schedule::Task::~Task() {
  if (0 != pthread_join(m_task, nullptr)) {
    spdlog::error("could not join task {}", getName());
  }
}

bool EAR::Schedule::Task::operator==(const Task &other) const {
  return 0 == getName().compare(other.getName());
}

bool EAR::Schedule::Task::operator!=(const Task &other) const {
  return !(*this == other);
}

void EAR::Schedule::Task::execute(void) {
  std::chrono::steady_clock::time_point begin;
  std::chrono::steady_clock::time_point end;
  std::chrono::microseconds elapsed;

  // while keyword is to prevent that any unwanted situation breaks blocking call
  while (0 != pthread_cond_wait(&m_start_cond_var, &m_start_mutex));
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

  spdlog::debug("task {} function is over", getName());
    
  return;
}
