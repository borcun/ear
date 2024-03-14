/**
 * @file task.h
 * @brief
 * @author boo
 */

#ifndef TASK_H
#define TASK_H

#include <thread>
#include <pthread.h>
#include <chrono>
#include "service_util.h"

namespace FACE {
    /// task interface
    class Task {
	friend class Scheduler;
	    
    public:
	/// constructor
	Task();
	/// destructor
	virtual ~Task();
	
	/// function that is supposed to be implemented by derived classes
	virtual void process() = 0;

    private:
	/// task for parellel execution of service function
	std::thread m_task;
	/// mutex used to give start to the task
	pthread_mutex_t m_mutex;
	/// start flag indicating state of the task
	bool m_is_started;
	/// task period in usec
	std::chrono::microseconds m_period;

	/// function that sets period of the service
	/// @param [in] period - service period in usec
	void setPeriod(const std::chrono::microseconds &period);
	/// function that starts task component service
	/// @param [in] cond_var - condition variable to be passed to execute
	/// @return true if service is started, otherwise false
	bool start(pthread_cond_t *cond_var);
	/// function that stops task component service
	/// @return true if service is stopped, otherwise false
	bool stop();	    
	/// function that executes service, and is scheduled by service task
	/// @param [in] cond_var - condition variable for synchronization by scheduler
	void execute(pthread_cond_t *cond_var);
    };
}

#endif
