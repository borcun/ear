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
	    /// function that allocate memory for task for scheduling
	    /// @param [in] task - task pointer
	    /// @param [in] period - task period in usec
	    /// @param [in] offset - task start offset in usec
	    /// @return true if the memory is allocated for task, otherwise false
	    bool allocate(Task *task, const uint32_t period, const uint32_t offset);
	    /// function that runs the scheduler
	    /// @pre the scheduler must be initialized firstly
	    /// @return true if the scheduler runs, otherwise false
	    bool start();
	    /// function that terminates the scheduler
	    /// @pre the scheduler must be run earlier
	    /// @return true if the scheduler is terminated, otherwise false
	    bool stop();
	    
	private:
	    /// task list
	    std::list<Task *> m_tasks;
	    /// state for state machine of the scheduler
	    State m_state;

	    // copyable and movable task interface prevented
	    Scheduler(const Scheduler &scheduler) = delete;
	    Scheduler(const Scheduler &&scheduler) = delete;
	    Scheduler &operator=(const Scheduler &scheduler) = delete;
	};
    }
}
