/**
 * @file endpoint.h
 * @brief class that provides communication infrastructure
 * @author boo
 */

#pragma once

#include <string>
#include "spdlog/spdlog.h"
#include "message.h"

namespace EAR {
    namespace Communication {
	/// communication state
	enum State {
	    COMM_CLOSED,
	    COMM_OPENED
	};

	/// endpoint configuration
	struct Configuration {
	    std::string ip;
	    uint16_t port;
	};

	/// class Endpoint
	class Endpoint {
	    friend class NetworkManager;
	
	public:
	    /// default constructor
	    Endpoint();
	    /// destructor
	    virtual ~Endpoint();
	    /// function that gets endpoint state
	    /// @return endpoint state
	    State getState() const;
	    /// function that initializes endpoint
	    /// @param [in] config - endpoint configuration
	    /// @return true if endpoint is initialized, otherwise false
	    virtual bool initialize(const Configuration &config) = 0;
	    /// function that shutdowns endpoint
	    virtual void shutdown() = 0;
	    
	protected:
	    /// endpoint state
	    State m_state = COMM_CLOSED;
	};
    }
}
