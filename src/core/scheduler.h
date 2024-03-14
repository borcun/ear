#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <set>
#include "task.h"

namespace FACE {
    /// scheduler state
    enum SchedulerState {
	SS_IDLE,
	SS_INIT,
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
	/// function that initializes the scheduler
	/// @pre task list must include task(s)
	/// @return true if the scheduler is initialized, otherwise false
	bool init();
	/// function that runs the scheduler
	/// @pre the scheduler must be initialized firstly
	/// @return true if the scheduler runs, otherwise false
	bool run();
	/// function that terminates the scheduler
	/// @pre the scheduler must be run earlier
	/// @return true if the scheduler is terminated, otherwise false
	bool terminate();
	    
    private:
	/// tasks
	std::set<Task *> m_tasks;
	/// condition variable to give start to all tasks at the same time
	pthread_cond_t m_cond_var;
	/// state for state machine of the scheduler
	SchedulerState m_state;
    };
}

#endif
