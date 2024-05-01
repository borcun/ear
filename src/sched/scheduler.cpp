#include "scheduler.h"

EAR::Schedule::Scheduler::Scheduler() {
    m_state = SCHEDULER_IDLE;
}

EAR::Schedule::Scheduler::~Scheduler()
{
}

bool EAR::Schedule::Scheduler::allocate(Task *task, const uint32_t period, const uint32_t offset) {
    if (nullptr == task) {
	spdlog::error("could not allocate memory for null task");
	return false;
    }

    if (period < TASK_MIN_PERIOD) {
	spdlog::error("invalid period value {} for task {}", period, task->getName());
	return false;
    }

    if (SCHEDULER_IDLE != m_state) {
	spdlog::error("could not allocate memory for {} when scheduler running", task->getName());
	return false;
    }

    if (!task->initialize()) {
	spdlog::error("could not initialize task {}", task->getName());
	return false;	
    }

    /// @todo check whether same element is added twice
    task->setPeriod(std::chrono::microseconds(period));
    task->setOffset(std::chrono::microseconds(offset));
    m_tasks.push_back(task);
    
    return true;
}

bool EAR::Schedule::Scheduler::start() {
    if (SCHEDULER_IDLE != m_state) {
	spdlog::error("could not run the scheduler that was already running");
	return false;
    }

    if (0 == m_tasks.size()) {
	spdlog::error("could not run the scheduler that is empty");
	return false;
    }

    for (auto &task : m_tasks) {
	if (!task->start()) {
	    spdlog::critical("could not start task {}", task->getName());
	}
	else {
	    spdlog::debug("Task {} started", task->getName());
	}
    }

    m_state = SCHEDULER_RUN;
    return true;
}

bool EAR::Schedule::Scheduler::stop() {
    if (SCHEDULER_RUN != m_state) {
	spdlog::error("could not stop the scheduler that not running");
	return false;
    }
    
    for (auto &task : m_tasks) {
	if (!task->stop()) {
	    spdlog::critical("could not stop task {}", task->getName());
	}
	else {
	    spdlog::debug("Task {} stopped", task->getName());
	}
    }

    m_state = SCHEDULER_IDLE;
    return true;
}
