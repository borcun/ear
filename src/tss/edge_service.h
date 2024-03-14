/**
 * @file edge_service.h
 * @brief
 * @author boo
 */

#ifndef EDGE_SERVICE_H
#define EDGE_SERVICE_H

#include "service.h"
#include "gateway.h"

namespace FACE {
    namespace TSS {
	class EdgeService : public Service {
	public:
	    /// constructor
	    /// @param [in] name - edge service name
	    EdgeService(const std::string &name);
	    /// destructor
	    virtual ~EdgeService();
	    /// function that connects edge services each other
	    /// @param [in] service - edge service
	    /// @return true if connection is done successfully, otherwise false
	    bool connect(const EdgeService *service);
	    /// function that sends buffer to subscribers
	    /// @param [in] buf - buffer
	    /// @param [in] size - buffer size
	    /// @return true if buffer is sent to subscribers, otherwise false
	    bool send(void *buf, size_t size);
	    /// function that receives buffer from publisher
	    /// @param [in] buf - buffer
	    /// @param [in|out] size - buffer size
	    /// @return true if buffer is received from publisher, otherwise false
	    bool receive(void *buf, size_t &size);

	private:
	    /// edge service gateway
	    Gateway *m_gateway = nullptr;
	};
    }
}

#endif
