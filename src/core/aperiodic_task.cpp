#include "aperiodic_task.h"

EAR::APeriodicTask::APeriodicTask() : EAR::Task() { }

EAR::APeriodicTask::~APeriodicTask() { }

void EAR::APeriodicTask::execute() {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::microseconds elapsed;
    
    pthread_cond_wait(&m_cond_var, &m_mutex);
    std::this_thread::sleep_for(std::chrono::microseconds(m_offset));
    
    do {
	begin = std::chrono::steady_clock::now();
	process();
	end = std::chrono::steady_clock::now();
	
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	if (elapsed <= m_period) {
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
	}
	else {
	    spdlog::warn("deadline missed for task {}", getId());
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
	}

	// wait start command for next iteration, then sleep offset before execution
	pthread_cond_wait(&m_cond_var, &m_mutex);
	std::this_thread::sleep_for(std::chrono::microseconds(m_offset));
    } while (m_is_running);
    
    return;
}
