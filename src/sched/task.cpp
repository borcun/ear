#include "task.h"

void *EAR::Schedule::__makeParallel(void *args) {
  EAR::Schedule::Task *task = static_cast<EAR::Schedule::Task *>(args);
    
  if (nullptr == task) {
    spdlog::critical("could not start task, because conversion failed");
  }
  else {
    task->execute();
  }
    
  return nullptr;
}

EAR::Schedule::Task::Task(const std::string &name) : EAR::Schedule::ITask(name) {
  pthread_create(&m_task, nullptr, __makeParallel, this);
}

EAR::Schedule::Task::~Task() {
  pthread_join(m_task, nullptr);
}

void EAR::Schedule::Task::execute() {
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
