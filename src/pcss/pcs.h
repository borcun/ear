/**
 * @file pcs.h
 * @brief
 * @author boo
 */

#ifndef PORTABLE_COMPONENT_SERVICE_H
#define PORTABLE_COMPONENT_SERVICE_H

#include "portable_service.h"

namespace FACE {
    namespace PCSS {
	class PortableComponentService : public PortableService {
	public:
	    /// constructor
	    /// @param [in] name - portable component service name
	    explicit PortableComponentService(const std::string &name);
	    /// destructor
	    virtual ~PortableComponentService();
	    /// function that is supposed to be implemented by derived classes
	    /// @remark its execution period is defined with setPeriod function
	    virtual void service();
	};
    }
}

#endif
