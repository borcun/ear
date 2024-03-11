/**
 * @file pcs.h
 * @brief
 * @author boo
 */

#ifndef PORTABLE_COMPONENT_SERVICE_H
#define PORTABLE_COMPONENT_SERVICE_H

#include "periodic_service.h"
#include "ts.h"

namespace FACE {
    namespace PCSS {
	class PortableComponentService : public PeriodicService {
	public:
	    /// constructor
	    /// @param [in] name - portable component service name
	    explicit PortableComponentService(const std::string &name);
	    /// destructor
	    virtual ~PortableComponentService();
	    /// function that sets transport service instance of portable component service
	    /// @param [in] tservice - transport service instance
	    void setTransportService(TSS::TransportService *tservice);
	    /// function that is supposed to be implemented by derived classes
	    /// @remark its execution period is defined with setPeriod function
	    virtual void service();
 	    
	protected:
	    /// transport service
	    TSS::TransportService *m_tservice = nullptr;
	};
    }
}

#endif
