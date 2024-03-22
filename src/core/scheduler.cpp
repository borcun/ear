#include "scheduler.h"

EAR::Scheduler::Scheduler() {
    m_state = SCHEDULER_IDLE;
}

EAR::Scheduler::~Scheduler() {

}

bool EAR::Scheduler::add(Task *task, const uint32_t &period) {
    if (nullptr == task || SCHEDULER_IDLE != m_state || period < TASK_MIN_PERIOD) {
	spdlog::error("could not add task {}", (nullptr != task ? task->getId() : -1));
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

bool EAR::Scheduler::start() {
    if (SCHEDULER_IDLE != m_state || 0 == m_tasks.size()) {
	spdlog::error("could not run the scheduler");
	return false;
    }
    
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it) {
	if (!(*it)->start()) {
	    spdlog::critical("could not start task {}", (*it)->getId());
	}
    }

    m_state = SCHEDULER_RUN;
    return true;
}

bool EAR::Scheduler::restart() {
    // restarting needs the task already started
    if (SCHEDULER_RUN != m_state || 0 == m_tasks.size()) {
	spdlog::error("could not restart the scheduler");
	return false;
    }
    
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it) {
	if (!(*it)->restart()) {
	    spdlog::critical("could not restart task {}", (*it)->getId());
	}
    }

    return true;
}

bool EAR::Scheduler::stop() {
    if (SCHEDULER_RUN != m_state) {
	spdlog::error("could not terminate the scheduler");
	return false;
    }
    
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it) {
	if (!(*it)->stop()) {
	    spdlog::critical("could not stop task {}", (*it)->getId());
	}
	else {
	    spdlog::info("task {} stopped", (*it)->getId());
	}
    }

    m_state = SCHEDULER_IDLE;
    return true;
}
