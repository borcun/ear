/**
 * @file task.h
 * @brief
 * @author boo
 */

#ifndef TASK_H
#define TASK_H

#include "core_util.h"

namespace EAR {
    /// task interface
    class Task {
	friend class Scheduler;
	    
    public:
	/// constructor
	Task();
	/// destructor
	virtual ~Task();
	/// function that gets task id
	/// @return task id
	uint32_t getId() const;
	/// function that is supposed to be implemented by derived classes
	virtual void process() = 0;

    protected:
	/// unique task id
	uint32_t m_id;
	/// task period in usec
	std::chrono::microseconds m_period;
	/// run flag indicating state of the task
	bool m_is_running;
	/// mutex used to give start to the task
	pthread_mutex_t m_mutex;
	/// start condition flag for the thread
	pthread_cond_t m_cond_var;
	
	/// function that sets period of the service
	/// @param [in] period - service period in usec
	void setPeriod(const std::chrono::microseconds &period);
	/// function that starts task component service
	/// @return true if service is started, otherwise false
	bool start();
	/// function that restarts task component service
	/// @return true if service is started, otherwise false
	virtual bool restart();
	/// function that stops task component service
	/// @return true if service is stopped, otherwise false
	bool stop();	    

	/// function that executes service, and is scheduled by service task
	virtual void execute() = 0;

    private:
	/// task for parellel execution of service function
	std::thread m_task;

	// copyable and movable task prevented
	Task(const Task &task) = delete;
	Task(const Task &&task) = delete;
	Task &operator=(const Task &task) = delete;
    };
}

#endif
