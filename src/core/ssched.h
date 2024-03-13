#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <map>
#include "portable_service.h"

namespace FACE {
    /// scheduler states
    enum SchedulerState {
	SS_IDLE,
	SS_INIT,
	SS_RUN
    };
	
    class ServiceScheduler {
    public:
	/// constructor
	ServiceScheduler();
	/// destructor
	virtual ~ServiceScheduler();
	/// function that adds a portable service into the scheduler
	/// @param [in] pserv - portable service pointer
	/// @return true if the service is added, otherwise false
	bool addService(PortableService *pserv);
	/// function that initializes the scheduler
	/// @pre portable service list must include service(s)
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
	/// portable services
	std::map<uint32_t, PortableService *> m_services;
	/// condition variable to give start to all portable services at the same time
	pthread_cond_t m_cond_var;
	/// state for state machine of the scheduler
	SchedulerState m_state;
    };
}

#endif
