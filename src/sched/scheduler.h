/**
 * @file scheduler.h
 * @brief task scheduler class
 * @author boo
 */

#pragma once

#include <list>
#include "task.h"

namespace EAR {
    namespace Schedule {
	/// scheduler state
	enum State {
	    SCHEDULER_IDLE,
	    SCHEDULER_RUN
	};
	
	class Scheduler {
	public:
	    /// default constructor
	    Scheduler();
	    /// destructor
	    virtual ~Scheduler();
	    /// function that adds a task into the scheduler
	    /// @param [in] task - task pointer
	    /// @param [in] period - task period in usec
	    /// @param [in] offset - task start offset in usec
	    /// @return true if the task is added, otherwise false
	    bool add(Task *task, const uint32_t period, const uint32_t offset);
	    /// function that runs the scheduler
	    /// @pre the scheduler must be initialized firstly
	    /// @return true if the scheduler runs, otherwise false
	    bool start();
	    /// function that restarts the scheduling
	    /// @return true if scheduling is restarted, otherwise false
	    bool restart();
	    /// function that terminates the scheduler
	    /// @pre the scheduler must be run earlier
	    /// @return true if the scheduler is terminated, otherwise false
	    bool stop();
	    
	private:
	    /// task list
	    std::list<Task *> m_tasks;
	    /// state for state machine of the scheduler
	    State m_state;
	};
    }
}
