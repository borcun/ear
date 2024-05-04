/**
 * @file endpoint.h
 * @brief class that provides communication infrastructure
 * @author boo
 */

#pragma once

#include <string>
#include <error.h>
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
	class Configuration {
	public:
	    std::string ip;
	    uint16_t port = 0;
	    bool is_blocked = false;
	    uint32_t timeout = 0U; // in msec
	};

	/// class Endpoint
	class Endpoint {
	    friend class NetworkManager;
	
	public:
	    /// constructor
	    /// @param [in] name - endpoint name
	    explicit Endpoint(const std::string &name);
	    /// destructor
	    virtual ~Endpoint();
	    /// function tht gets endpoint name
	    /// @return name of endpoint
	    std::string getName() const;
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

	private:
	    /// endpoint name
	    std::string m_name;
	};
    }
}
