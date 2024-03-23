#include "scheduler.h"

EAR::Scheduler::Scheduler() {
    m_state = SCHEDULER_IDLE;
}

EAR::Scheduler::~Scheduler() {

}

bool EAR::Scheduler::add(Task *task, const uint32_t period, const uint32_t offset) {
    if (nullptr == task) {
	spdlog::error("could not add null task");
	return false;
    }

    if (SCHEDULER_IDLE != m_state || period < TASK_MIN_PERIOD) {
	spdlog::error("could not add task {}", task->getId());
	return false;
    }

    /// @todo check whether same element is added twice
    task->setPeriod(std::chrono::microseconds(period));
    task->setOffset(std::chrono::microseconds(offset));
    m_tasks.push_back(task);
    
    return true;
}

bool EAR::Scheduler::start() {
    if (SCHEDULER_IDLE != m_state || 0 == m_tasks.size()) {
	spdlog::error("could not run the scheduler");
	return false;
    }

    for (auto &task : m_tasks) {
	if (!task->start()) {
	    spdlog::critical("could not start task {}", task->getId());
	}
    }

    m_state = SCHEDULER_RUN;
    return true;
}

bool EAR::Scheduler::restart() {
    if (SCHEDULER_RUN != m_state || 0 == m_tasks.size()) {
	spdlog::error("could not restart the scheduler");
	return false;
    }
    
    for (auto &task : m_tasks) {
	if (!task->restart()) {
	    spdlog::critical("could not restart task {}", task->getId());
	}
    }

    return true;
}

bool EAR::Scheduler::stop() {
    if (SCHEDULER_RUN != m_state) {
	spdlog::error("could not terminate the scheduler");
	return false;
    }
    
    for (auto &task : m_tasks) {
	if (!task->stop()) {
	    spdlog::critical("could not stop task {}", task->getId());
	}
	else {
	    spdlog::info("task {} stopped", task->getId());
	}
    }

    m_state = SCHEDULER_IDLE;
    return true;
}
