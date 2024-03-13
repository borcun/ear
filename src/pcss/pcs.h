/**
 * @file pcs.h
 * @brief
 * @author boo
 */

#ifndef PORTABLE_COMPONENT_SERVICE_H
#define PORTABLE_COMPONENT_SERVICE_H

#include "periodic_service.h"
#include "channel.h"

namespace FACE {
    namespace PCSS {
	class PortableComponentService : public PeriodicService {
	public:
	    /// constructor
	    /// @param [in] name - portable component service name
	    explicit PortableComponentService(const std::string &name);
	    /// destructor
	    virtual ~PortableComponentService();
	    /// function that sets transport service channel for portable component service
	    /// @param [in] channel - transport service channel
	    void setChannel(TSS::Channel *channel);
	    /// function that is supposed to be implemented by derived classes
	    /// @remark its execution period is defined with setPeriod function
	    virtual void service();
 	    
	protected:
	    /// transport service channel
	    TSS::Channel *m_channel = nullptr;
	};
    }
}

#endif
