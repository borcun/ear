/**
 * @file listener.h
 * @brief class that provides receiving/listening infrastructure for message transfer
 * @author boo
 */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "endpoint.h"

namespace EAR {
    namespace Communication {
	/// class Listener
	class Listener : public Endpoint {
	public:
	    /// constructor
	    /// @param [in] name - endpoint name
	    explicit Listener(const std::string &name);
	    /// destructor
	    virtual ~Listener();
	    /// function that sets timeout of message listener
	    /// @remark default time is zero
	    /// @param [in] timeout - message listener receive timeout
	    void setTimeout(const int32_t timeout);
	    /// function that receives buffer from the publisher
	    /// @param [in] buf - buffer
	    /// @param [in|out] size - buffer size
	    /// @return true if buffer is received from the publisher, otherwise false
	    bool receive(void *buf, size_t &size);

	    virtual bool initialize(const Configuration &config) override;
	    virtual void shutdown() override;

	private:
	    /// socket
	    int m_sock = -1;
	    /// receive timeout
	    int32_t m_timeout = 0;
	};
    }
}
