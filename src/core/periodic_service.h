/**
 * @file periodic_service.h
 * @brief
 * @author boo
 */

#ifndef PERIODIC_SERVICE_H
#define PERIODIC_SERVICE_H

#include <thread>
#include <pthread.h>
#include <chrono>
#include "service.h"

namespace FACE {
    class PeriodicService : public Service {
	friend class ServiceScheduler;
	    
    public:
	/// constructor
	/// @param [in] name - portable component service name
	explicit PeriodicService(const std::string &name);
	/// destructor
	virtual ~PeriodicService();
	/// function that sets period of the service
	/// @param [in] period - service period in usec
	void setPeriod(const std::chrono::microseconds &period);
	
	/// function that is supposed to be implemented by derived classes
	virtual void service() = 0;
 	    
    private:
	/// task for parellel execution of service function
	std::thread m_task;
	/// mutex used to give start to the task
	pthread_mutex_t m_mutex;
	/// start flag indicating state of the task
	bool m_is_started;
	/// task period in usec
	std::chrono::microseconds m_period;

	/// function that starts portable component service
	/// @param [in] cond_var - condition variable to be passed to execute
	/// @return true if service is started, otherwise false
	bool start(pthread_cond_t *cond_var);
	/// function that stops portable component service
	/// @return true if service is stopped, otherwise false
	bool stop();	    
	/// function that executes service, and is scheduled by service task
	/// @param [in] cond_var - condition variable for synchronization by scheduler
	void execute(pthread_cond_t *cond_var);
    };
}

#endif
