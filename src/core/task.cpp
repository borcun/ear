#include "task.h"
#include "spdlog/spdlog.h"

FACE::Task::Task() {
  m_is_started = false;
  m_period = std::chrono::microseconds(TASK_MIN_PERIOD);
  pthread_mutex_init(&m_mutex, NULL);
}

FACE::Task::~Task() {
    pthread_mutex_destroy(&m_mutex);
}

void FACE::Task::setPeriod(const std::chrono::microseconds &period) {
    // do not change task period when task is running
    if (m_is_started) {
	spdlog::error("could not change period after start");
    }
    else {
	m_period = std::chrono::microseconds(period);
    }
    
    return;
}

bool FACE::Task::start(pthread_cond_t *cond_var) {
    if (m_is_started) {
	spdlog::error("task already started");
	return false;
    }

    m_is_started = true;
    m_task = std::thread([=] { this->execute(cond_var); });
    
    return true;
}

bool FACE::Task::stop() {
    if (!m_is_started) {
	spdlog::error("task already stopped");
	return false;
    }

    m_is_started = false;
    m_task.join();

    return true;
}

void FACE::Task::execute(pthread_cond_t *cond_var) {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::microseconds elapsed;

    // wait order from scheduler
    pthread_cond_wait(cond_var, &m_mutex);
    
    while (m_is_started) {
	begin = std::chrono::steady_clock::now();
	process();
	end = std::chrono::steady_clock::now();
	
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	// sleep time remain after task execution
	if (elapsed <= m_period) {
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
	}
	else {
	    spdlog::warn("deadline missed");
	    std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
	}
    }

    return;
}
