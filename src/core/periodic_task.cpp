#include "periodic_task.h"

EAR::PeriodicTask::PeriodicTask() : EAR::Task()
{
}

EAR::PeriodicTask::~PeriodicTask() {
}


bool EAR::PeriodicTask::restart() {
    spdlog::warn("could not restart periodic task");
    return false;
}

void EAR::PeriodicTask::execute() {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::microseconds elapsed;

    // wait order from start
    pthread_cond_wait(&m_cond_var, &m_mutex);
    std::this_thread::sleep_for(std::chrono::microseconds(m_offset));
    
    do {
	begin = std::chrono::steady_clock::now();
	process();
	end = std::chrono::steady_clock::now();
	
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	// sleep time remain after task execution
	if (elapsed <= m_period) {
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
	}
	else {
	    spdlog::warn("deadline missed for task {}", getId());
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
	}
    } while (m_is_running);

    return;
}
