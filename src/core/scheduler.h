#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <set>
#include "task.h"

namespace FACE {
    /// scheduler state
    enum SchedulerState {
	SS_IDLE,
	SS_RUN
    };
	
    class Scheduler {
    public:
	/// constructor
	Scheduler();
	/// destructor
	virtual ~Scheduler();
	/// function that adds a task into the scheduler
	/// @param [in] task - task pointer
	/// @param [in] period - task period
	/// @return true if the task is added, otherwise false
	bool add(Task *task, const uint32_t &period = TASK_MIN_PERIOD);
	/// function that runs the scheduler
	/// @pre the scheduler must be initialized firstly
	/// @return true if the scheduler runs, otherwise false
	bool start();
	///
	bool restart();
	/// function that terminates the scheduler
	/// @pre the scheduler must be run earlier
	/// @return true if the scheduler is terminated, otherwise false
	bool stop();
	    
    private:
	/// tasks
	std::set<Task *> m_tasks;
	/// state for state machine of the scheduler
	SchedulerState m_state;
    };
}

#endif
