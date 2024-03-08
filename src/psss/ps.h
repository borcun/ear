/**
 * @file ps.h
 * @brief base class for platform-specific service segment
 * @author boo
 * @copyright
 */

#ifndef PLATFORM_SERVICE_H
#define PLATFORM_SERVICE_H

#include <thread>
#include <pthread.h>
#include <chrono>
#include "ios.h"
#include "ts.h"

/// minimum period in usec
#define PS_MIN_PERIOD (100000U)

namespace FACE {
    namespace PSSS {
	class PlatformService : public Service {
	    friend class PSScheduler;
	    
	public:
	    /// constructor
	    /// @param [in] name - platform service name
	    PlatformService(const std::string &name);
	    /// destructor
	    virtual ~PlatformService();
	    /// function that sets io service instance of platform service
	    /// @param [in] ioservice - io service instance
	    void setIOService(IOSS::IOService *ioservice);
	    /// function that sets transport service instance of platform service
	    /// @param [in] tservice - transport service instance
	    void setTransportService(TSS::TransportService *tservice);
	    /// function that sets period of the service
	    /// @param [in] period - service period in usec
	    void setPeriod(const std::chrono::microseconds &period);

	    /// function that is called periodically
	    virtual void service();
	    
	protected:
	    /// io service
	    IOSS::IOService *m_ioservice = nullptr;
	    /// transport service
	    TSS::TransportService *m_tservice = nullptr;

	private:
	    /// task
	    std::thread m_task;
	    /// mutex
	    pthread_mutex_t m_mutex;
	    /// start flag
	    bool m_is_started;
	    /// task period
	    std::chrono::microseconds m_period;

	    /// function that starts platform service
	    /// @param [in] cond_var - condition variable to be passed to execute
	    /// @return true if service is started, otherwise false
	    bool start(pthread_cond_t *cond_var);
	    /// function that stops platform service
	    /// @return true if service is stopped, otherwise false
	    bool stop();
	    
	    /// function that executes service, and is scheduled by service task
	    /// @param [in] cond_var - condition variable for synchronization by scheduler
	    void execute(pthread_cond_t *cond_var);
	};
    }
}

#endif
