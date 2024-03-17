/**
 * @file ps.h
 * @brief base class for platform-specific service segment
 * @author boo
 * @copyright
 */

#ifndef PLATFORM_SERVICE_H
#define PLATFORM_SERVICE_H

#include "edge_service.h"
#include "aperiodic_task.h"
#include "ios.h"

namespace FACE {
    namespace PSSS {
	class PlatformService : public TSS::EdgeService, public APeriodicTask {
	public:
	    /// constructor
	    /// @param [in] name - platform service name
	    explicit PlatformService(const std::string &name);
	    /// destructor
	    virtual ~PlatformService();
	    /// function that sets io service instance of platform service
	    /// @param [in] ioservice - io service instance
	    void setIOService(IOSS::IOService *ioservice);
	    /// function that is supposed to be implemented by derived classes
	    /// @remark its execution period is defined with setPeriod function
	    virtual void process();
	    
	protected:
	    /// io service
	    IOSS::IOService *m_ioservice = nullptr;
	};
    }
}

#endif
