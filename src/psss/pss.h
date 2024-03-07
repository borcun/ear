/**
 * @file ps.h
 * @brief
 * @author boo
 * @copyright
 */

#ifndef PLATFORM_SERVICE_H
#define PLATFORM_SERVICE_H

#include <thread>
#include "ios.h"
#include "ts.h"

namespace FACE {
    namespace PSSS {
	class PlatformService : public Service {
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
	    /// function that starts platform service
	    /// @return true if service is started, otherwise false
	    bool start();
	    /// function that stops platform service
	    /// @return true if service is stopped, otherwise false
	    bool stop();
	    
	    /// function that is called periodically
	    virtual void process();
	    
	protected:
	    /// io service supposed to be used in process()
	    IOSS::IOService *m_ioservice = nullptr;
	    /// transport service supposed to be used in process()
	    TSS::TransportService *m_tservice = nullptr;

	private:
	    /// task that runs schedule()
	    std::thread m_task;
	    /// start flag
	    bool m_is_started = false;

	    /// function that is scheduled by task
	    void schedule();
	};
    }
}

#endif
