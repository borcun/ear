/**
 * @file portable_service.h
 * @brief
 * @author boo
 */

#ifndef PORTABLE_SERVICE_H
#define PORTABLE_SERVICE_H

#include <thread>
#include <pthread.h>
#include <chrono>
#include "service.h"
#include "channel.h"

namespace FACE {
    class PortableService : public Service {
	friend class ServiceScheduler;
	    
    public:
	/// constructor
	/// @param [in] name - portable component service name
	explicit PortableService(const std::string &name);
	/// destructor
	virtual ~PortableService();
	/// function that sets period of the service
	/// @param [in] period - service period in usec
	void setPeriod(const std::chrono::microseconds &period);
	/// function that sets transport service channel for platform service
	/// @param [in] channel - transport service channel
	void setChannel(TSS::Channel *channel);
	/// function that is supposed to be implemented by derived classes
	virtual void service() = 0;

    protected:
	/// transport service channel
	TSS::Channel *m_channel = nullptr;

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
