/**
 * @file task.h
 * @brief task interface class
 * @author boo
 */

#ifndef TASK_H
#define TASK_H

#include <threads.h>
#include <chrono>
#include "spdlog/spdlog.h"
#include "util.h"

namespace EAR {
    int doParallel(void *args);
  
    /// task interface class
    class Task {
	// scheduler uses task instances
	friend class Scheduler;
        friend int doParallel(void *args);
      
    public:
	/// default constructor
	Task();
	/// destructor
	virtual ~Task();
	/// function that gets task id
	/// @return task id
        uint32_t getId() const;
	/// function that is supposed to be implemented by task user
	virtual void process() = 0;

    protected:
	/// task period in usec
	std::chrono::microseconds m_period;
	/// task start offset in usec
	std::chrono::microseconds m_offset;
	/// run flag indicating state of the task
	bool m_is_running;
	/// mutex used to give start to the task
	mtx_t m_mutex;
	/// start condition flag for the thread
	cnd_t m_cond_var;
	
	/// function that sets period of the task
	/// @param [in] period - task period in usec
	void setPeriod(const std::chrono::microseconds period);
	/// function that sets offset of the task
	/// @param [in] offset - offset to sleep before execution
	void setOffset(const std::chrono::microseconds offset);	
	/// function that starts task
	/// @return true if task is started, otherwise false
	bool start();
	/// function that restarts task
	/// @return true if task is started, otherwise false
	virtual bool restart();
	/// function that stops task
	/// @return true if task is stopped, otherwise false
	bool stop();
	/// function that is execution body of the task, specific to task algorithm
	/// @remark it is supposed to be implemented by class based on task derived
	virtual void execute() = 0;

    private:
	/// task
	thrd_t m_task;
	/// task id
	uint32_t m_id;

	// copyable and movable task prevented
	Task(const Task &task) = delete;
	Task(const Task &&task) = delete;
	Task &operator=(const Task &task) = delete;
    };
}

#endif
