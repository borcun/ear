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
	/// task for parellel execution of task function
	std::thread m_task;
	/// task period in usec
	std::chrono::microseconds m_period;
	/// task start offset in usec
	std::chrono::microseconds m_offset;
	/// run flag indicating state of the task
	bool m_is_running;
	/// mutex used to give start to the task
	pthread_mutex_t m_mutex;
	/// start condition flag for the thread
	pthread_cond_t m_cond_var;
	
	/// function that sets period of the task
	/// @param [in] period - task period in usec
	void setPeriod(const std::chrono::microseconds period);
	/// function that sets offset of the task
	/// @param [in] offset - offset to sleep before execution
	void setOffset(const std::chrono::microseconds offset);	
	/// function that starts task component task
	/// @return true if task is started, otherwise false
	bool start();
	/// function that restarts task component task
	/// @return true if task is started, otherwise false
	virtual bool restart();
	/// function that stops task component task
	/// @return true if task is stopped, otherwise false
	bool stop();
	/// function that is execution body of the task 
	virtual void execute() = 0;

    private:
	// copyable and movable task prevented
	Task(const Task &task) = delete;
	Task(const Task &&task) = delete;
	Task &operator=(const Task &task) = delete;
    };
}

#endif
