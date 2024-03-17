/**
 * @file pcs.h
 * @brief
 * @author boo
 */

#ifndef PORTABLE_COMPONENT_SERVICE_H
#define PORTABLE_COMPONENT_SERVICE_H

#include "edge_service.h"
#include "periodic_task.h"

namespace FACE {
    namespace PCSS {
	class PortableComponentService : public TSS::EdgeService, public PeriodicTask {
	public:
	    /// constructor
	    /// @param [in] name - portable component service name
	    explicit PortableComponentService(const std::string &name);
	    /// destructor
	    virtual ~PortableComponentService();
	    /// function that is supposed to be implemented by derived classes
	    /// @remark its execution period is defined with setPeriod function
	    virtual void process();
	};
    }
}

#endif
