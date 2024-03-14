#include "scheduler.h"

FACE::Scheduler::Scheduler() {
    m_state = SS_IDLE;
    pthread_cond_init(&m_cond_var, NULL);
}

FACE::Scheduler::~Scheduler() {
    pthread_cond_destroy(&m_cond_var);
}

bool FACE::Scheduler::add(Task *task, const uint32_t &period) {
    if (nullptr == task || SS_IDLE != m_state || period < TASK_MIN_PERIOD) {
	spdlog::error("could not add task");
	return false;
    }

    auto it = m_tasks.insert(task);

    if (m_tasks.end() == it.first) {
	spdlog::error("could not add task already in the list");
	return false;
    }

    task->setPeriod(std::chrono::microseconds(period));
    
    return true;
}

bool FACE::Scheduler::init() {
    if (SS_IDLE != m_state || 0 == m_tasks.size()) {
	spdlog::error("could not initialize the scheduler");
	return false;
    }
    
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it) {
	if (!(*it)->start(&m_cond_var)) {
	    spdlog::critical("could not start task");
	}
	else {
	    /// @todo wait some because of duration of thread create, solve it!!!
	    std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
    }

    m_state = SS_INIT;    
    return true;
}

bool FACE::Scheduler::run() {
    if (SS_INIT != m_state) {
	spdlog::error("could not run the scheduler");
	return false;
    }

    pthread_cond_broadcast(&m_cond_var);
    m_state = SS_RUN;

    return true;
}

bool FACE::Scheduler::terminate() {
    if (SS_RUN != m_state) {
	spdlog::error("could not terminate the scheduler");
	return false;
    }
    
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it) {
	if (!(*it)->stop()) {
	    spdlog::critical("could not stop task");
	}
    }

    m_state = SS_IDLE;
    return true;
}
