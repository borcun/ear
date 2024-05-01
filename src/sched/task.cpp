#include "task.h"

void *EAR::Schedule::makeParallel(void *args) {
  ((EAR::Schedule::Task *) args)->execute();
  return nullptr;
}

EAR::Schedule::Task::Task(const std::string &name) : EAR::Schedule::ITask(name) {
    spdlog::debug("task {} created", name);
    pthread_create(&m_task, nullptr, makeParallel, this);
}

EAR::Schedule::Task::~Task() {
    pthread_join(m_task, nullptr);
    spdlog::debug("task {} terminated", getName());
}

void EAR::Schedule::Task::execute() {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::microseconds elapsed;
    
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
	    spdlog::warn("deadline missed for task {}", getName());
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
	}
    } while (m_is_running);

    spdlog::debug("task {} execution done", getName());
    
    return;
}
