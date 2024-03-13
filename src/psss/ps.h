/**
 * @file ps.h
 * @brief base class for platform-specific service segment
 * @author boo
 * @copyright
 */

#ifndef PLATFORM_SERVICE_H
#define PLATFORM_SERVICE_H

#include "periodic_service.h"
#include "ios.h"
#include "channel.h"

namespace FACE {
    namespace PSSS {
	class PlatformService : public PeriodicService {
	public:
	    /// constructor
	    /// @param [in] name - platform service name
	    explicit PlatformService(const std::string &name);
	    /// destructor
	    virtual ~PlatformService();
	    /// function that sets io service instance of platform service
	    /// @param [in] ioservice - io service instance
	    void setIOService(IOSS::IOService *ioservice);
	    /// function that sets transport service channel for platform service
	    /// @param [in] channel - transport service channel
	    void setChannel(TSS::Channel *channel);
	    /// function that is supposed to be implemented by derived classes
	    /// @remark its execution period is defined with setPeriod function
	    virtual void service();
	    
	protected:
	    /// io service
	    IOSS::IOService *m_ioservice = nullptr;
	    /// transport service channel
	    TSS::Channel *m_channel = nullptr;
	};
    }
}

#endif
