#include "aperiodic_task.h"

FACE::APeriodicTask::APeriodicTask(const std::string &name) : FACE::Task(name) {
}

FACE::APeriodicTask::~APeriodicTask() {
}

void FACE::APeriodicTask::execute() {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::microseconds elapsed;
    
    // wait order from initial start or restart command 
    pthread_cond_wait(&m_cond_var, &m_mutex);

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
	    spdlog::warn("deadline missed [{}]", m_name);
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
	}

	// wait order from start for each iteration
	pthread_cond_wait(&m_cond_var, &m_mutex);
    } while (m_is_running);
    
    return;
}
